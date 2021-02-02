#include "pch.h"

#ifdef _DEBUG
#include "cim/cim.h"
#include "cim/base/Log.h"

void testRegisterUser() {
    cim::ChatKitConfig config;
    config.serverInfo.ip = "10.0.107.244";

    if (cim::initChatKit(config) != cim::kSuccess) {
        return;
    }

    std::string u = "user123";
    std::string pwd = "sa123456";
    std::string nick = "user123";

    cim::core::HttpResponseBase res;

    if (!cim::core::UserManager::getInstance()->registerUser(u, pwd, nick, res)) {
        LogWarn("ÍøÂç´íÎó");

    } else {
        LogInfo("result code={},msg={}", res.code, res.msg);
    }
}

#endif // _DEBUG