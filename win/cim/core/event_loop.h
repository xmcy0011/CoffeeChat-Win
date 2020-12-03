/** @file event_loop.h
  * @brief event_loop
  * @author fei.xu
  * @date 2020/8/26
  */

#ifndef _EVENT_LOOP_CFF84E36_30AF_43D8_B263_CDBF4B55BBC8_
#define _EVENT_LOOP_CFF84E36_30AF_43D8_B263_CDBF4B55BBC8_

#include "cim_dll.h"
#include "base/noncopyable.h"
#include "asio.hpp"

namespace cim {
    namespace core {
        class CIM_DLL_API EventLoop : noncopyable {
        public:
            EventLoop();
            ~EventLoop() =default;

            asio::io_context &getLoop();

        private:
            asio::io_context* io_context_;
        };
    }
}
#endif//_EVENT_LOOP_CFF84E36_30AF_43D8_B263_CDBF4B55BBC8_



