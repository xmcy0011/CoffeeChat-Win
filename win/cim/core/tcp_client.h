/** @file TcpClient.h
  * @brief TcpClient
  * @author fei.xu
  * @date 2020/8/26
  */

#ifndef _TCPCLIENT_2E029671_CF33_4CE8_9F84_FF10E3867D55_
#define _TCPCLIENT_2E029671_CF33_4CE8_9F84_FF10E3867D55_

#include <string>
#include <cstdint>

#include "cim.h"
#include "base/noncopyable.h"
#include "event_loop.h"
#include "asio.hpp"

using namespace std;

namespace cim {
    namespace core {
        class CIM_DLL_API TcpClient : public cim::noncopyable {
        public:
            typedef std::shared_ptr<asio::ip::tcp::socket> SocketPtr;
            TcpClient();
            //TcpClient(EventLoop &loop);

            ~TcpClient();

            virtual void connect(string ip, uint16_t port);

            virtual void reconnect();

            virtual void disconnect();

            virtual ConnectStatus connStatus();

            virtual int sendRaw(const char *data, const int &len);

            virtual int send(CIM::Def::CIMCmdID cmd_id, const char *data, const int &len);

            virtual int sendRequest();

        private:
            asio::io_context io_context_;
            SocketPtr socket_;
            //EventLoop &loop_;

            ConnectStatus conn_status_;
            uint8_t *buffer_;
        };
    }
}

#endif//_TCPCLIENT_2E029671_CF33_4CE8_9F84_FF10E3867D55_