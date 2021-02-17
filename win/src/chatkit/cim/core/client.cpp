#include "pch.h"
#include "cim/core/client.h"
#include "cim/base/Log.h"

#include <evpp/event_loop.h>
#include <evpp/event_loop_thread.h>
#include <evpp/tcp_conn.h>
#include <evpp/tcp_client.h>
#include <evpp/buffer.h>

#include "cim/cim.h"
#include "cim/crypt/md5.h"

#include "cim/pb/CIM.Def.pb.h"
#include "cim/pb/CIM.Login.pb.h"

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
            // start loop
            loop_->Start(true);
        }

        Client::~Client() {
            logout();
            loop_->Stop(true);
        }

        Client* Client::getInstance() {
            static Client client;
            return &client;
        }

        void Client::login(std::string user_name, std::string pwd, const LoginCallback& cb, const TimeoutCallback& timeout_cb) {
            logout();

            conn_status_ = kConnectting;
            login_cb_ = cb;
            login_timeout_cb_ = timeout_cb;

            MD5 md;
            md.update(pwd);

            user_name_ = user_name;
            user_pwd_ = md.toString(); // md5

            std::string end_point = cim::getChatKitConfig().serverInfo.ip + ":" + std::to_string(cim::getChatKitConfig().serverInfo.gatePort);

            if (tcp_client_ == nullptr) {
                tcp_client_ = std::make_unique<evpp::TCPClient>(loop_.get()->loop(), end_point, "tcp_client");

                // bind callback
                tcp_client_->SetConnectionCallback(std::bind(&Client::onConnectionStatusChanged, this, std::placeholders::_1));
                tcp_client_->SetMessageCallback(std::bind(&Client::onMessage, this, std::placeholders::_1, std::placeholders::_2));

            } else {

            }

            tcp_client_->Connect();
            LogInfo("connect server,userName={},pwd={}", user_name, user_pwd_);
        }

        void Client::setConnectionCallback(const ConnectionCallback& cb) {
            connection_cb_ = cb;
        }

        void Client::logout() {
            if (is_login_) {
                is_login_ = false;
                CIM::Login::CIMLogoutReq req;
                req.set_user_id(user_id_);
                req.set_client_type(CIM::Def::kCIM_CLIENT_TYPE_PC_WINDOWS);
                send(CIM::Def::kCIM_CID_LOGIN_AUTH_LOGOUT_REQ, req);
            }

            if (tcp_client_) {
                tcp_client_->Disconnect();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                tcp_client_ = nullptr;
            }
        }

        ConnectStatus Client::connStatus() {
            return conn_status_;
        }

        evpp::EventLoop* Client::connLoop() {
            return loop_.get()->loop();
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

            LogInfo("connection status={}", conn_status_);

            // 登录请求
            if (!is_login_ && conn_status_ == kConnectOk) {
                CIM::Login::CIMAuthReq req;
                req.set_user_name(user_name_);
                req.set_user_pwd(user_pwd_);
                req.set_client_version(kClientVersion);
                req.set_client_type(CIM::Def::kCIM_CLIENT_TYPE_PC_WINDOWS);
                send(CIM::Def::kCIM_CID_LOGIN_AUTH_REQ, req);
                LogInfo("connect success, login ... userName={},pwd={}", user_name_, user_pwd_);
            }

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
                header.len = static_cast<uint32_t>(buffer->ReadInt32());			// 头+数据部的总长
                int reset_len = buffer->length() - header.len + sizeof(uint32_t);	// 注意已读4字节

                // 坏包，数据部长度超过buffer里面的，全部丢弃。
                if (header.len - sizeof(uint32_t) > buffer->size()) {
                    break;
                }

                if (header.len < kMaxBufferLen) {
                    header.version = static_cast<uint16_t>(buffer->ReadInt16());
                    header.flag = static_cast<uint16_t>(buffer->ReadInt16());
                    header.service_id = static_cast<uint16_t>(buffer->ReadInt16());
                    header.cmd = static_cast<uint16_t>(buffer->ReadInt16());
                    header.seq = static_cast<uint16_t>(buffer->ReadInt16());
                    header.reserved = static_cast<uint16_t>(buffer->ReadInt16());

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
            case CIM::Def::kCIM_CID_LOGIN_AUTH_RSP:
                onHandleAuthRsp(header, buffer);
                break;

            default:
                LogInfo("unknown cmd={}", header->cmd);
                buffer->Skip(header->len);
                break;
            }
        }

        uint16_t Client::getSeq() {
            ++seq_;
            return seq_;
        }

        void Client::onHandleAuthRsp(const IMHeader* header, evpp::Buffer* buffer) {
            CIM::Login::CIMAuthRsp rsp;

            PARSE_PB_AND_CHECK(rsp, buffer);

            LogInfo("result_code={},result_string={}", rsp.result_code(), rsp.result_string());

            if (login_cb_) {
                login_cb_(rsp);
            }
        }
    }
}