/** @file cim_tcp_client.h
  * @brief cim_tcp_client
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _CIM_TCP_CLIENT_616739B1_29BC_4B6A_825B_F6250ACC9BC4_
#define _CIM_TCP_CLIENT_616739B1_29BC_4B6A_825B_F6250ACC9BC4_

#include "cim.h"
#include "cim/base/noncopyable.h"
#include "asio.hpp"
#include "cim_conn_base.h"

using asio::ip::tcp;

namespace cim {

    class CIMTcpClient : cim::noncopyable, public IClientConn {
      public:
        CIMTcpClient();
        ~CIMTcpClient();

      public:
        void connect(string ip, uint16_t port) override;
        void reconnect() override;
        void disconnect() override;
        ConnectStatus connStatus()override;

        int sendRaw(const char* data, const int& len) override;
        int send(CIMCmdID cmd_id, const char* data, const int& len)override;
        int sendRequest() override;

      private:
        /*asio::io_context& io_context_;*/
        tcp::socket socket_;
    };

    IClientConn* getClientConn();
    void startEventLoop();
}

#endif//_CIM_TCP_CLIENT_616739B1_29BC_4B6A_825B_F6250ACC9BC4_
