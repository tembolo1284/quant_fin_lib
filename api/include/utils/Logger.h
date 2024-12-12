#ifndef QUANT_FIN_API_LOGGER_H
#define QUANT_FIN_API_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace quant_fin {
namespace api {

class Logger {
public:
    static void init(const std::string& logPath = "logs") {
        try {
            // Create console sink
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::debug);

            // Create daily rotating file sink
            auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
                logPath + "/api.log", 0, 0);
            file_sink->set_level(spdlog::level::trace);

            // Create loggers with both sinks
            std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
            
            auto api_logger = std::make_shared<spdlog::logger>("API", sinks.begin(), sinks.end());
            api_logger->set_level(spdlog::level::debug);
            api_logger->flush_on(spdlog::level::debug);
            
            spdlog::register_logger(api_logger);

            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [%t] %v");

        } catch (const spdlog::spdlog_ex& ex) {
            std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        }
    }

    static std::shared_ptr<spdlog::logger> getLogger() {
        return spdlog::get("API");
    }
};

} // namespace api
} // namespace quant_fin

// Custom logging macros that won't conflict with Drogon
#define API_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(quant_fin::api::Logger::getLogger(), __VA_ARGS__)
#define API_LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(quant_fin::api::Logger::getLogger(), __VA_ARGS__)
#define API_LOG_INFO(...) SPDLOG_LOGGER_INFO(quant_fin::api::Logger::getLogger(), __VA_ARGS__)
#define API_LOG_WARN(...) SPDLOG_LOGGER_WARN(quant_fin::api::Logger::getLogger(), __VA_ARGS__)
#define API_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(quant_fin::api::Logger::getLogger(), __VA_ARGS__)
#define API_LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(quant_fin::api::Logger::getLogger(), __VA_ARGS__)

#endif // QUANT_FIN_API_LOGGER_H
