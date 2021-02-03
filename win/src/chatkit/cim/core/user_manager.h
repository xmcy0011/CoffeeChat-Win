/** @file im_user_manager.h
  * @brief im_user_manager
  * @author teng.qing
  * @date 2021/1/15
  */

#ifndef _IM_USER_MANAGER_F51B4D37_8EE2_425D_8E93_7AD84E14CA08_
#define _IM_USER_MANAGER_F51B4D37_8EE2_425D_8E93_7AD84E14CA08_

#include "cim/base/noncopyable.h"
#include "cim/cim_def.h"
#include "cim/cim_dll.h"

namespace cim {
    namespace core {
        struct HttpResponseBase {
            int code;
            std::string msg;
        };

        class CIM_DLL_API UserManager: cim::noncopyable {
          public:
            static UserManager* getInstance();

          public:
            bool registerUser(std::string userName, std::string userPwd, std::string nickName, HttpResponseBase& out);

          private:
            UserManager();
            ~UserManager() = default;
        };
    }
}

#endif//_IM_USER_MANAGER_F51B4D37_8EE2_425D_8E93_7AD84E14CA08_