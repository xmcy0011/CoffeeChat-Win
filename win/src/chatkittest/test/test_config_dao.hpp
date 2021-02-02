#ifndef _TEST_CONFIG_DAO_3D3276B0_052A_4D3D_9FC9_8E2BB959FCB4_
#define _TEST_CONFIG_DAO_3D3276B0_052A_4D3D_9FC9_8E2BB959FCB4_

#include "cim/cim.h"
#include "cim/db/config_dao.h"

void testQueryUserConfig() {
    cim::db::IMConfig data;
    cim::db::ConfigDao::getInstance()->query(data);

    std::cout << "ip = " << data.serverIp << ",gatePort=" << data.gatePort << ",httpPort=" << data.httpPort << std::endl;
}
void testUpdateUserConfig() {
    cim::db::ConfigDao::getInstance()->updateServerIp("192.168.1.1");

    cim::db::IMConfig data;
    cim::db::ConfigDao::getInstance()->query(data);
    std::cout << "new ip=" << data.serverIp << std::endl;
}

#endif//_TEST_CONFIG_DAO_3D3276B0_052A_4D3D_9FC9_8E2BB959FCB4_