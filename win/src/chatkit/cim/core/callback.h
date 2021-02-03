#ifndef _CALLBACK_B57DBE2E_86BB_48A9_A66F_B5AD9FC4EDF9_
#define _CALLBACK_B57DBE2E_86BB_48A9_A66F_B5AD9FC4EDF9_

/** @file callback.h
  * @brief callback
  * @author fei.xu
  * @date 2021/1/18
  */

#include <string>

#include "cim/pb/CIM.Def.pb.h"
#include "cim/pb/cim.Login.pb.h"

namespace cim {
    namespace core {
        // client.h
        typedef std::function<void(const CIM::Login::CIMAuthRsp& rsp)> LoginCallback;

        // user_manager.h
        //typedef std::function<void(uint32_t code, std::string msg)> HttpBaseCallback;
    }
}

#endif//_CALLBACK_B57DBE2E_86BB_48A9_A66F_B5AD9FC4EDF9_