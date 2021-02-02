#ifndef _CONFIG_MANAGER_C8190332_0B92_4D5F_9DC7_56C4F94B08C1_
#define _CONFIG_MANAGER_C8190332_0B92_4D5F_9DC7_56C4F94B08C1_

#include <string>
#include "cim/cim.h"
#include "cim/base/noncopyable.h"

namespace cim {
    namespace db {

        class CIM_DLL_API ConfigDao : noncopyable {
          public:
            static ConfigDao* getInstance();

            // crud
            bool createTable() noexcept;
            bool query(ConfigServerInfo& out) noexcept;

            void updateServerIp(const std::string& ip) noexcept;
            void updateMsgPort(const uint16_t& msgPort) noexcept;
            void updateHttpPort(const uint16_t& httpPort) noexcept;

            // get/set
            bool queryKey(const std::string& key, std::string& outValue) noexcept;
            void updateKey(const std::string& key, const std::string& newValue) noexcept;

          private:
            void insertDefaultData();

          private:
            ConfigDao();
            ~ConfigDao();
        };
    }
}

#endif//_CONFIG_MANAGER_C8190332_0B92_4D5F_9DC7_56C4F94B08C1_