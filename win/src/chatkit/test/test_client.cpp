#ifdef _DEBUG
#include "cim.h"
#include "base/Log.h"

void testClient() {
    using namespace cim::core;

    cim::ChatKitConfig config;
    config.serverIp = "10.0.107.244";

    if (cim::initChatKit(config) != kSuccess) {
        return;
    }

    Client* client = Client::getInstance();

    client->setConnectionCallback([](const ConnectStatus & status) {
        LogInfo("connection status changed:{}", status);
    });
    client->login("1008", "123456", [](const CIM::Login::CIMAuthTokenRsp & rsp) {
        LogInfo("login result={}", rsp.result_code() == CIM::Def::kCIM_ERR_SUCCSSE);
    }, nullptr);

    std::this_thread::sleep_for(std::chrono::hours(1));
}

#endif // _DEBUG