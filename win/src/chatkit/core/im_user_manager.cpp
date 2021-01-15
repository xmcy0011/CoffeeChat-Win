#include "im_user_manager.h"

namespace cim {
    namespace core {
        IMUserManager* IMUserManager::getInstance() {
            static IMUserManager instance;
            return &instance;
        }

        IMUserManager::IMUserManager() = default;


    }
}


