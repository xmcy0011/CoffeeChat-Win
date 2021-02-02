/** @file Log.h
  * @brief Log
  * @author fei.xu
  * @date 2020/8/24
  */

#ifndef _LOG_0B0512CC_B1CC_4483_AF05_1914E7F7D4DA_
#define _LOG_0B0512CC_B1CC_4483_AF05_1914E7F7D4DA_

#include <string>
#include <corecrt_io.h>

#ifndef SPDLOG_TRACE_ON
#define SPDLOG_TRACE_ON
#endif

#ifndef SPDLOG_DEBUG_ON
#define SPDLOG_DEBUG_ON
#endif

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#endif


//定义一个在日志后添加 文件名 函数名 行号 的宏定义.
#ifndef suffix
#define suffix(msg)  std::string(msg).append("  <")\
            .append(__FILENAME__).append("> <").append(__FUNCTION__) \
			.append("> <").append(std::to_string(__LINE__)) \
			.append(">").c_str()
#endif

#include "cim/cim_dll.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace cim {
    class CIM_DLL_API ZLogger {
      public:
        auto GetLogger() {
            return nml_logger;
        }

        ZLogger();
        ~ZLogger();
        ZLogger(const ZLogger&) = delete;
        ZLogger& operator=(const ZLogger&) = delete;

      private:
        std::shared_ptr<spdlog::logger> nml_logger;
    };
}
CIM_DLL_API cim::ZLogger& GetInstance();

#define SPDLOG_LOGGER_CALL_(level, ...) GetInstance().GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)
#define LogTrace(...)  SPDLOG_LOGGER_CALL_(spdlog::level::trace,__VA_ARGS__)
#define LogDebug(...)  SPDLOG_LOGGER_CALL_(spdlog::level::debug,__VA_ARGS__)
#define LogInfo(...)   SPDLOG_LOGGER_CALL_(spdlog::level::info,__VA_ARGS__)
#define LogWarn(...)   SPDLOG_LOGGER_CALL_(spdlog::level::warn,__VA_ARGS__)
#define LogError(...)  SPDLOG_LOGGER_CALL_(spdlog::level::err,__VA_ARGS__)
#define LogCritical(...) SPDLOG_LOGGER_CALL_(spdlog::level::critical,__VA_ARGS__)
#define LogCriticalIf(b, ...)               \
    do {                                  		    \
			if ((b)) {               			  \
				 SPDLOG_LOGGER_CALL_(spdlog::level::critical,__VA_ARGS__); \
			}                                      \
	} while (0)

#ifdef WIN32
#define errcode WSAGetLastError()
#endif

#endif//_LOG_0B0512CC_B1CC_4483_AF05_1914E7F7D4DA_