#include "Log.h"

cim::ZLogger m_instance;
cim::ZLogger& GetInstance() {
    return m_instance;
}

namespace cim {
    ZLogger::ZLogger() {
        if (::_access("logs", 0) == -1) {
            ::_mkdir("logs");
        }

        //����Ϊ�첽��־
        //spdlog::set_async_mode(32768);  // ����Ϊ 2 ����
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

        // ������־��¼����
#ifdef _DEBUG
        nml_logger->set_level(spdlog::level::trace);
#else
        nml_logger->set_level(spdlog::level::info);
#endif

        //���õ����� err ������صĴ���ʱ����ˢ����־��  disk .
        nml_logger->flush_on(spdlog::level::warn);

        spdlog::set_pattern("%Y-%m-%d %H:%M:%S [%l] [%t] - <%s>|<%#>|<%!>,%v");
        spdlog::flush_every(std::chrono::seconds(2));

    }

    ZLogger::~ZLogger() {
        spdlog::drop_all();
    }
}