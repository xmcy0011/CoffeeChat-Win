#ifndef _CHAT_MANAGER_87388056_6B36_4D6E_9B52_29714A89AD17_
#define _CHAT_MANAGER_87388056_6B36_4D6E_9B52_29714A89AD17_

#include "cim/base/noncopyable.h"
#include "cim/base/Log.h"
#include "cim/cim_dll.h"
#include <string>

namespace cim {
    namespace core {
        class CIM_DLL_API ChatManager: public noncopyable {
          public:
            static ChatManager& getInstance();
            static std::wstring FormatMsgTime(const int64_t& msgTimeStamp);

          private:
            ChatManager();
            ~ChatManager();
        };

        //void CIM_DLL_API testFormatMsgTime();
    }
}

#endif//_CHAT_MANAGER_87388056_6B36_4D6E_9B52_29714A89AD17_