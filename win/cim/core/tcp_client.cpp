#include "tcp_client.h"
#include "base/Log.h"

//asio::io_context g_io_context_;
//std::atomic_uint16_t g_seq = 1;
const uint32_t kMaxBufferLen = 1024 * 10;// 10 KB

namespace cim {
    namespace core {
        TcpClient::TcpClient(/*EventLoop &loop*/) :  /*loop_(loop), socket_(g_io_context_£©,*/ conn_status_(kDefault) {
            buffer_ = new uint8_t(kMaxBufferLen);
            ::memset(buffer_, 0, kMaxBufferLen);
            socket_ = make_shared<asio::ip::tcp::socket>(io_context_);
            //socket_ = new asio::ip::tcp::socket(loop.getLoop());

            std::thread t([this]() {
                LogInfo("io_context run...");
                this->io_context_.run();
                LogInfo("io_context exit...");
            });
            t.detach();
        }

        TcpClient::~TcpClient() {

        }

        void TcpClient::connect(string ip, uint16_t port) {
            try {
                conn_status_ = kConnectting;
//                asio::ip::tcp::resolver resolver(g_io_context_);
//                asio::ip::tcp::resolver::results_type endpoints =
//                    resolver.resolve(ip + ":" + std::to_string(port), "daytime");
                asio::error_code ec;
                asio::ip::address_v4 ipv4_address = asio::ip::make_address_v4(ip, ec);
                asio::ip::tcp::endpoint ep(asio::ip::address(ipv4_address)/*asio::ip::address::from_string(ip)*/, port);
                socket_->connect(ep, ec);

                if (ec) {
                    LogWarn(ec.message());
                    conn_status_ = kDisConnect;
                    return;
                }

                conn_status_ = kConnectOk;

            } catch (std::exception &e) {
                LogWarn(e.what());
                conn_status_ = kDisConnect;
            }
        }

        void TcpClient::reconnect() {

        }

        void TcpClient::disconnect() {

        }

        ConnectStatus TcpClient::connStatus() {
            return kDefault;
        }

        int TcpClient::sendRaw(const char *data, const int &len) {
            return 0;
        }

        int TcpClient::send(CIM::Def::CIMCmdID cmd_id, const char *data, const int &len) {
            return 0;
        }

        int TcpClient::sendRequest() {
            return 0;
        }

    }
}