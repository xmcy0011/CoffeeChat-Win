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


#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace cim {
    class ZLogger {
      public:
        static ZLogger& GetInstance() {
            static ZLogger m_instance;
            return m_instance;
        }

        auto GetLogger() {
            return nml_logger;
        }

        ZLogger() {

            if (::_access("logs", 0) == -1) {
                ::_mkdir("logs");
            }

            //设置为异步日志
            //spdlog::set_async_mode(32768);  // 必须为 2 的幂
            std::vector<spdlog::sink_ptr> sinkList;

#if 1
            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleSink->set_level(spdlog::level::debug);
            //consoleSink->set_pattern("[multi_sink_example] [%^%l%$] %v");
            //consoleSink->set_pattern("[%m-%d %H:%M:%S.%e][%^%L%$]  %v");
            consoleSink->set_pattern("%Y-%m-%d %H:%M:%S [%l] [%t] - <%s>|<%#>|<%!>,%v");
            sinkList.push_back(consoleSink);
#endif
            auto dailySink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/log.log", 2, 30);
            dailySink->set_level(spdlog::level::debug);
            sinkList.push_back(dailySink);

            nml_logger = std::make_shared<spdlog::logger>("both", begin(sinkList), end(sinkList));
            //register it if you need to access it globally
            spdlog::register_logger(nml_logger);

            // 设置日志记录级别
#ifdef _DEBUG
            nml_logger->set_level(spdlog::level::trace);
#else
            nml_logger->set_level(spdlog::level::info);
#endif

            //设置当出发 err 或更严重的错误时立刻刷新日志到  disk .
            nml_logger->flush_on(spdlog::level::warn);

            spdlog::set_pattern("%Y-%m-%d %H:%M:%S [%l] [%t] - <%s>|<%#>|<%!>,%v");
            spdlog::flush_every(std::chrono::seconds(2));

        }

        ~ZLogger() {
            spdlog::drop_all();
        }

        ZLogger(const ZLogger&) = delete;
        ZLogger& operator=(const ZLogger&) = delete;

      private:
        std::shared_ptr<spdlog::logger> nml_logger;

    };

#define SPDLOG_LOGGER_CALL_(level, ...) ZLogger::GetInstance().GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)
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
}


#endif//_LOG_0B0512CC_B1CC_4483_AF05_1914E7F7D4DA_