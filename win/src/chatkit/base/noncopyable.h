/** @file noncopyable.h
  * @brief noncopyable
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _NONCOPYABLE_377FD72A_191C_4A10_805E_E43301C78BDC_
#define _NONCOPYABLE_377FD72A_191C_4A10_805E_E43301C78BDC_

#include "../cim_dll.h"

namespace cim {
    class CIM_DLL_API noncopyable {
      public:
        // 拷贝构造删除
        noncopyable(const noncopyable&) = delete;
        // 赋值构造删除
        void operator=(const noncopyable&) = delete;

      protected:
        noncopyable() = default;
        virtual ~noncopyable() = default;
    };
}

#endif//_NONCOPYABLE_377FD72A_191C_4A10_805E_E43301C78BDC_