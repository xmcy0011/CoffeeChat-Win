#include "cim_tcp_client.h"
#include "cim/base/Log.h"
#include <thread>

namespace cim {
    asio::io_context g_io_context_;

    CIMTcpClient::CIMTcpClient(): socket_(g_io_context_) {
    }

    CIMTcpClient::~CIMTcpClient() {
    }

    IClientConn* getClientConn() {
        static CIMTcpClient client;
        return static_cast <IClientConn*>(&client);
    }

    void startEventLoop() {
        std::thread t([]() {
            g_io_context_.run();
            LogDebug("asio::io_context exit.");
        });
        t.detach();
    }

    void CIMTcpClient::connect(string ip, uint16_t port) {

    }
    void CIMTcpClient::reconnect() {

    }
    void CIMTcpClient::disconnect() {

    }
    ConnectStatus CIMTcpClient::connStatus() {
        return ConnectStatus::kDisConnect;
    }

    int CIMTcpClient::sendRaw(const char* data, const int& len) {
        return 0;
    }
    int CIMTcpClient::send(CIMCmdID cmd_id, const char* data, const int& len) {
        return 0;
    }
    int CIMTcpClient::sendRequest() {
        return 0;
    }
}

