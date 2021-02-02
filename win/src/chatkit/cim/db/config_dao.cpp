#include "pch.h"
#include "cim/db/config_dao.h"

namespace cim {
    namespace db {
        ConfigDao* ConfigDao::getInstance() {
            static ConfigDao instance;
            return &instance;
        }

        ConfigDao::ConfigDao() {
        }

        ConfigDao::~ConfigDao() {
        }
    }
}