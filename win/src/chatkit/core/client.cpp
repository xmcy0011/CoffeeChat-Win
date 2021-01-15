#include "pch.h"
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

const std::string kClientVersion = "0.1"; // 客户端类型

namespace cim {
    namespace core {
        Client::Client() :
            conn_status_(kDefault),
            tcp_client_(nullptr),
            loop_(nullptr),
            user_id_(0),
            is_login_(false) {
            loop_ = std::make_unique<evpp::EventLoopThread>();
        }

        Client::~Client() {
        }

        Client* Client::getInstance() {
            static Client client;
            return &client;
        }

        void Client::login(std::string user_name, std::string pwd, string ip, uint16_t port, const LoginCallback& cb, const TimeoutCallback& timeout_cb) {
            conn_status_ = kConnectting;
            login_cb_ = cb;
            login_timeout_cb_ = timeout_cb;

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
            is_login_ = false;

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
            header.len = sizeof(IMHeader) +  msg.ByteSize();
            header.version = kProtocolVersion;

            evpp::Buffer buffer(header.len);
            buffer.AppendInt32((int32_t)header.len);
            buffer.AppendInt16((int16_t)kProtocolVersion);
            buffer.AppendInt16(0);
            buffer.AppendInt16(0);
            buffer.AppendInt16((int16_t)header.cmd);
            buffer.AppendInt16((int16_t)header.seq);
            buffer.AppendInt16(0);

            //buffer.Write(&header, sizeof(IMHeader));
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

            // 登录请求
            if (!is_login_ && conn_status_ == kConnectOk) {
                CIM::Login::CIMAuthTokenReq req;
                req.set_user_id(user_id_);
                req.set_user_token(user_token_);
                req.set_client_version(kClientVersion);
                req.set_client_type(CIM::Def::kCIM_CLIENT_TYPE_PC_WINDOWS);
                send(CIM::Def::kCIM_CID_LOGIN_AUTH_TOKEN_REQ, req);
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

            // tcp 粘包
            while (true) {
                IMHeader header = { 0 };
                header.len = static_cast<uint32_t>(buffer->PeekInt32());
                int reset_len = buffer->length() - header.len;

                if (header.len < kMaxBufferLen) {
                    header.version = static_cast<uint16_t>(buffer->PeekInt16());
                    header.flag = static_cast<uint16_t>(buffer->PeekInt16());
                    header.service_id = static_cast<uint16_t>(buffer->PeekInt16());
                    header.cmd = static_cast<uint16_t>(buffer->PeekInt16());
                    header.seq = static_cast<uint16_t>(buffer->PeekInt16());
                    header.reserved = static_cast<uint16_t>(buffer->PeekInt16());

                    if (header.len >= buffer->size()) {
                        break;
                    }

                    onHandleData(&header, buffer);

                    assert(reset_len == buffer->length());
                    //buffer->Skip(header->len);

                    if (buffer->length() <= 0) {
                        break;

                    } else if (buffer->length() < sizeof(IMHeader)) {
                        LogWarn("packet not full");
                        break;
                    }

                } else {
                    LogWarn("to large packet,len={}", buffer->size());
                    break;
                }
            }

            buffer->Reset();
        }

        void Client::onHandleData(const IMHeader* header, evpp::Buffer* buffer) {
            LogDebug("cmd={},seq={},len={}", header->cmd, header->seq, header->len);

            switch (header->cmd) {
            case CIM::Def::kCIM_CID_LOGIN_AUTH_TOKEN_RSP:
                onHandleAuthRsp(header, buffer);

            default:
                LogInfo("unknown cmd={}", header->cmd);
                break;
            }
        }

        uint16_t Client::getSeq() {
            ++seq_;
            return seq_;
        }

        void Client::onHandleAuthRsp(const IMHeader* header, evpp::Buffer* buffer) {
            CIM::Login::CIMAuthTokenRsp rsp;

            PARSE_PB_AND_CHECK(rsp, buffer);

            LogInfo("result_code={},result_string={}", rsp.result_code(), rsp.result_string());

            if (login_cb_) {
                login_cb_(rsp);
            }
        }
    }
}