#ifndef _CONFIG_MANAGER_C8190332_0B92_4D5F_9DC7_56C4F94B08C1_
#define _CONFIG_MANAGER_C8190332_0B92_4D5F_9DC7_56C4F94B08C1_

#include <string>
#include "cim/base/noncopyable.h"

namespace cim {
    namespace db {
        struct IMConfig {
            std::string serverIp;
            uint16_t gatePort;
            uint16_t httpPort;
        };

        class CIM_DLL_API ConfigDao : noncopyable {
          public:
            static ConfigDao* getInstance();

            // crud
            bool createTable() noexcept;
            bool query(IMConfig& out) noexcept;

            void updateServerIp(const std::string& ip) noexcept;
            void updateMsgPort(const uint16_t& msgPort) noexcept;
            void updateHttpPort(const uint16_t& httpPort) noexcept;

          private:
            void insertDefaultData();
            void updateKey(std::string key, std::string newValue) noexcept;

          private:
            ConfigDao();
            ~ConfigDao();
        };
    }
}

#endif//_CONFIG_MANAGER_C8190332_0B92_4D5F_9DC7_56C4F94B08C1_