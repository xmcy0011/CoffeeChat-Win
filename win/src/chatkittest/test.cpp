#include <iostream>

#include "cim/cim.h"

// test
#include "test/test_client.h"
#include "test/test_user_manager.h"
#include "test/test_config_dao.hpp"

int main() {
    cim::ChatKitConfig config;
    cim::initChatKit(config);

    // 注册用户
    //testLogin();
    //testRegisterUser();

    //testQueryUserConfig();
    testUpdateUserConfig();

    cim::cleanup();
}