#include "pch.h"

#ifdef _DEBUG
#include "cim/cim.h"
#include "cim/base/Log.h"

void testLogin() {
    using namespace cim::core;

    cim::ChatKitConfig config;
    config.serverInfo.ip = "10.0.107.244";

    std::string u = "user123";
    std::string pwd = "sa123456";

    if (cim::initChatKit(config) != cim::kSuccess) {
        return;
    }

    Client* client = Client::getInstance();

    client->setConnectionCallback([](const ConnectStatus & status) {
        LogInfo("connection status changed:{}", status);
    });
    client->login(u, pwd, [](const CIM::Login::CIMAuthRsp & rsp) {
        LogInfo("login result={}", rsp.result_code() == CIM::Def::kCIM_ERR_SUCCSSE);

        if (rsp.result_code() != CIM::Def::kCIM_ERR_SUCCSSE) {
            Client::getInstance()->logout();
        }
    }, nullptr);

    std::this_thread::sleep_for(std::chrono::hours(1));
}

#endif // _DEBUG