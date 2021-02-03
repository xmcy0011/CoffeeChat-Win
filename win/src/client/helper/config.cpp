#include "stdafx.h"
#include "config.h"
#include "cim/cim.h"

const std::string kUserNameKey = "userName";
const std::string kUserPwdKey = "pwdHash";

Config* Config::getInstace() {
    static Config instance;
    return &instance;
}

void Config::load() {
    std::string v;

    if (cim::db::ConfigDao::getInstance()->queryKey(kUserNameKey, v )) {
        userName = v;
    }

    /*if (cim::db::ConfigDao::getInstance()->queryKey(kUserPwdKey, v)) {
    	pwdMd5 = v;
    }*/

    LogInfo("load config from sqlite3, userName={},pwdHash={}", userName, pwdMd5);
}

void Config::save() {
    auto dao = cim::db::ConfigDao::getInstance();
    dao->updateKey(kUserNameKey, userName);
}
