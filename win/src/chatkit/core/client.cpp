#include "client.h"
#include "base/Log.h"

#include <evpp/event_loop_thread.h>
#include <evpp/tcp_conn.h>
#include <evpp/tcp_client.h>
#include <evpp/buffer.h>

#include "pb/CIM.Def.pb.h"
#include "pb/CIM.Login.pb.h"

//std::atomic_uint16_t g_seq = 1;
const uint32_t kMaxBufferLen = 1024 * 10;// 10 KB

namespace cim {
    namespace core {
        Client::Client() : conn_status_(kDefault), tcp_client_(nullptr), loop_(nullptr), user_id_(0) {
            loop_ = std::make_unique<evpp::EventLoopThread>();
        }

        Client::~Client() {
        }

        Client* Client::getInstance() {
            static Client client;
            return &client;
        }

        void Client::login(std::string user_name, std::string pwd, string ip, uint16_t port) {
            conn_status_ = kConnectting;

            std::string end_point = ip + ":" + std::to_string(port);

            if (tcp_client_ == nullptr) {
                tcp_client_ = std::make_unique<evpp::TCPClient>(loop_.get()->loop(), end_point, "tcp_client");

                // bind callback
                tcp_client_->SetConnectionCallback(std::bind(&Client::onConnectionStatusChanged, this, std::placeholders::_1));
                tcp_client_->SetMessageCallback(std::bind(&Client::onMessage, this, std::placeholders::_1, std::placeholders::_2));

                // start loop
                loop_->Start(true);
            }

            tcp_client_->Connect();
        }

        void Client::setConnectionCallback(const ConnectionCallback& cb) {
            connection_cb_ = cb;
        }

        void Client::logout() {
            CIM::Login::CIMLogoutReq req;
            req.set_user_id(user_id_);
            req.set_client_type(CIM::Def::kCIM_CLIENT_TYPE_IOS);
            send(CIM::Def::kCIM_CID_LOGIN_AUTH_LOGOUT_REQ, req);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tcp_client_->Disconnect();
        }

        ConnectStatus Client::connStatus() {
            return kDefault;
        }

        int Client::sendRaw(const char* data, const int& len) {
            return 0;
        }

        int Client::send(CIM::Def::CIMCmdID cmd_id, const google::protobuf::MessageLite& msg) {
            LogDebug("cmd_id={},bodyLen={}", cmd_id, msg.ByteSize());

            IMHeader header = { 0 };
            header.cmd = cmd_id;
            header.seq = getSeq();

            evpp::Buffer buffer(sizeof(IMHeader) + msg.ByteSize());
            buffer.Write(&header, sizeof(IMHeader));
            msg.SerializeToArray(buffer.WriteBegin(), msg.ByteSize());
            buffer.WriteBytes(msg.ByteSize());

            if (conn_status_ == kConnectOk && tcp_client_->conn()) {
                tcp_client_->conn()->Send(&buffer);
                return buffer.length();

            } else {
                LogWarn("connection disconnect");
            }

            return kError;
        }

        int Client::sendRequest() {
            return 0;
        }

        void Client::onConnectionStatusChanged(const evpp::TCPConnPtr& conn) {
            if (conn->IsConnecting()) {
                conn_status_ = kConnectOk;

            } else if (conn->IsConnected()) {
                conn_status_ = kConnectOk;

            } else if (conn->IsDisconnected()) {
                conn_status_ = kDisConnect;

            } else {
                conn_status_ = kDefault;
            }

            LogInfo("connection status={}", conn_status_);

            if (connection_cb_) {
                connection_cb_(conn_status_);
            }
        }

        void Client::onMessage(const evpp::TCPConnPtr& conn, evpp::Buffer* buffer) {
            LogDebug("remoteIp={},dataLen={}", conn->remote_addr(), buffer->size());

            if (buffer->size() <= sizeof(IMHeader)) {
                LogWarn("bad packet");
                return;
            }

            // tcp Õ³°ü
            while (true) {
                IMHeader* header = (IMHeader*)buffer->data();
                buffer->Skip(sizeof(IMHeader));

                if (header->len < kMaxBufferLen) {

                    if (header->len >= buffer->size()) {
                        break;
                    }

                } else {
                    LogWarn("to large packet,len={}", buffer->size());
                    break;
                }
            }

            buffer->Reset();
        }

        uint16_t Client::getSeq() {
            ++seq_;
            return seq_;
        }
    }
}