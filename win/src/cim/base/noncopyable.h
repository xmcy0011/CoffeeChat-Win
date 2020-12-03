/** @file noncopyable.h
  * @brief noncopyable
  * @author fei.xu
  * @date 2020/8/20
  */

#ifndef _NONCOPYABLE_377FD72A_191C_4A10_805E_E43301C78BDC_
#define _NONCOPYABLE_377FD72A_191C_4A10_805E_E43301C78BDC_

#include "cim_dll.h"

namespace cim {
    class CIM_DLL_API noncopyable {
      public:
        // ���ÿ�������
        noncopyable(const noncopyable&) = delete;
        // ���ø�ֵ
        void operator=(const noncopyable&) = delete;

      protected:
        noncopyable() = default;
        ~noncopyable() = default;
    };
}

#endif//_NONCOPYABLE_377FD72A_191C_4A10_805E_E43301C78BDC_