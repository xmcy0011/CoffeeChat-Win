#ifdef _DEBUG

#include "cim.h"
#include "base/Log.h"

#include "core/user_manager.h"

void testRegisterUser() {
    cim::ChatKitConfig config;
    config.serverIp = "10.0.107.244";

    if (cim::initChatKit(config) != kSuccess) {
        return;
    }

    std::string u = "user123";
    std::string pwd = "sa123456";
    std::string nick = "²âÊÔ×¢²áÓÃ»§";

    cim::core::HttpResponseBase res;

    if (!cim::core::UserManager::getInstance()->registerUser(u, pwd, nick, res)) {
        LogWarn("ÍøÂç´íÎó");

    } else {
        LogInfo("result code={},msg={}", res.code, res.msg);
    }
}

#endif // _DEBUG