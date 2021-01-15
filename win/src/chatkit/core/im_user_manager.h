/** @file im_user_manager.h
  * @brief im_user_manager
  * @author teng.qing
  * @date 2021/1/15
  */

#ifndef _IM_USER_MANAGER_F51B4D37_8EE2_425D_8E93_7AD84E14CA08_
#define _IM_USER_MANAGER_F51B4D37_8EE2_425D_8E93_7AD84E14CA08_

#include "cim.h"

namespace cim {
    namespace core {
        class IMUserManager: cim::noncopyable {
          public:
            static IMUserManager* getInstance();

          public:
            //bool registerUser();

          private:
            IMUserManager();
            ~IMUserManager() = default;
        };
    }
}

#endif//_IM_USER_MANAGER_F51B4D37_8EE2_425D_8E93_7AD84E14CA08_