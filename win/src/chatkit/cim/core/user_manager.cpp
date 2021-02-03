#include "pch.h"
#include "user_manager.h"

#include "cim/cim.h"
#include "cim/core/client.h"
#include "cim/crypt/md5.h"
#include "cim/base/Log.h"

#include "json/json.h"

#include <restclient-cpp/restclient.h>

namespace cim {
    namespace core {

        const double kHttpTimeout = 3; // s
        const std::string kUrlRegisterUser = "/user/register";

        const std::string kDefaultHttpErrorMsg = "Î´Öª´íÎó";

        UserManager* UserManager::getInstance() {
            static UserManager instance;
            return &instance;
        }

        bool UserManager::registerUser(std::string userName, std::string userPwd, std::string nickName, HttpResponseBase& out) {
            std::string url = "http://" + cim::getChatKitConfig().serverInfo.ip + ":" + std::to_string(cim::getChatKitConfig().serverInfo.httpPort) + kUrlRegisterUser;

            MD5 md;
            md.update(userPwd);
            std::string pwd = md.toString();

            Json::Value root;
            root["userName"] = userName;
            root["userNickName"] = nickName;
            root["userPwd"] = pwd;

            LogInfo("register url={},userName={},userPwd={},nickName={}", url, userName, pwd, nickName);

            auto res = RestClient::post(url, "application/json; charset=utf-8", root.toStyledString());

            if (res.code != 200) {
                return false;

            } else {
                Json::Value value;
                std::unique_ptr<Json::Reader> reader = std::make_unique<Json::Reader>(Json::Features::strictMode());

                if (reader->parse(res.body, value)) {
                    out.code = value["error_code"].asInt();
                    out.msg = value["error_msg"].asString();

                    LogInfo("register code={},msg={}", out.code, out.msg);
                }
            }
        }

        UserManager::UserManager() = default;
    }
}
