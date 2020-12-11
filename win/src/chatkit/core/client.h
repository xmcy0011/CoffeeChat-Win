/** @file TcpClient.h
  * @brief TcpClient
  * @author fei.xu
  * @date 2020/8/26
  */

#ifndef _TCPCLIENT_2E029671_CF33_4CE8_9F84_FF10E3867D55_
#define _TCPCLIENT_2E029671_CF33_4CE8_9F84_FF10E3867D55_

#include <string>
#include <cstdint>
#include <memory>
#include <functional>

#include "cim.h"
#include "cim_def.h"
#include "pb/CIM.Def.pb.h"
#include "base/noncopyable.h"

#include <google/protobuf/message_lite.h>

using namespace std;

namespace evpp {
    class TCPClient;
    class EventLoopThread;
    class Buffer;
    class TCPConn;
    typedef std::shared_ptr<evpp::TCPConn> TCPConnPtr;
}

namespace cim {
    namespace core {
        enum ConnectStatus {
            kDefault,
            kConnectting,
            kConnectOk,
            kDisConnect
        };
        typedef std::function<void(const ConnectStatus& status)> ConnectionCallback;
        typedef std::function<void(IMHeader&, evpp::Buffer* data)> MessageCallback;

        class CIM_DLL_API Client : public cim::noncopyable {
          public:
            /** @fn
              * @brief 获取单例，线程安全
              * @param
              * @return
              */
            static Client* getInstance();

            /** @fn
              * @brief 连接，会自动重连。非线程安全
              * @param
              * @return
              */
            void login(std::string user_name, std::string pwd, string ip, uint16_t port);
            void setConnectionCallback(const ConnectionCallback& cb);
            void logout();

            ConnectStatus connStatus();

            int sendRaw(const char* data, const int& len);

            int send(CIM::Def::CIMCmdID cmd_id, const google::protobuf::MessageLite& msg);

            int sendRequest();

          private:
            void onConnectionStatusChanged(const evpp::TCPConnPtr& conn);
            void onMessage(const evpp::TCPConnPtr& conn, evpp::Buffer* buffer);
            uint16_t getSeq();

          protected:
            Client();
            ~Client();

          private:
            std::unique_ptr<evpp::TCPClient> tcp_client_;
            std::unique_ptr<evpp::EventLoopThread> loop_;

            ConnectStatus conn_status_;

            ConnectionCallback connection_cb_;
            uint64_t user_id_;
            atomic<uint16_t> seq_;
        };
    }
}

#endif//_TCPCLIENT_2E029671_CF33_4CE8_9F84_FF10E3867D55_