#include <iostream>

#include "core/client.h"
#include "base/Log.h"

using namespace cim::core;

int main(int argc, char* argv) {
    cim::ChatKitConfig config;

    if (cim::initChatKit(config) != kSuccess) {
        return -1;
    }

    Client* client = Client::getInstance();

    client->setConnectionCallback([](const ConnectStatus & status) {
        LogInfo("connection status changed:{}", status);
    });
    client->login("1008", "123456", "10.0.107.244", 8000, [](const CIM::Login::CIMAuthTokenRsp & rsp) {
        LogInfo("login result={}", rsp.result_code() == CIM::Def::kCIM_ERR_SUCCSSE);
    }, nullptr);

    std::this_thread::sleep_for(std::chrono::hours(1));
    return 0;
}