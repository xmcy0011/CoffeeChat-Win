/** @file Exception.h
  * @brief Exception
  * @author fei.xu
  * @date 2020/8/24
  */

#ifndef _EXCEPTION_9AB0125B_1F4C_44CB_AFA3_B7202E02D3F4_
#define _EXCEPTION_9AB0125B_1F4C_44CB_AFA3_B7202E02D3F4_

#include <string>
#include <exception>

#include "cim/cim_dll.h"

using std::string;

namespace cim {
    class CIM_DLL_API Exception : public std::exception {
      public:
        Exception(string what);
        ~Exception() noexcept override = default;

        // default copy-ctor and operator= are okay.

        const char* what() const noexcept override {
            return message_.c_str();
        }

        const char* stackTrace() const noexcept {
            return stack_.c_str();
        }

      private:
        string message_;
        string stack_;
    };

};

#endif//_EXCEPTION_9AB0125B_1F4C_44CB_AFA3_B7202E02D3F4_
