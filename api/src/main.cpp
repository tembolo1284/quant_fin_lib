#include <drogon/drogon.h>
#include "filters/CorsFilter.h"
#include "utils/Logger.h"
#include "controllers/PricingController.h"
#include <iostream>
#include <filesystem>

int main() {
    try {
        // Create logs directory if it doesn't exist
        std::filesystem::create_directories("logs");

        // Initialize logger
        quant_fin::api::Logger::init();
        API_LOG_INFO("Starting Quantitative Finance API server");
        API_LOG_DEBUG("Initializing server configuration");

        // Configure server
        auto& app = drogon::app();
        
        // Load config and setup
        app.loadConfigFile("config.json");
        app.addListener("0.0.0.0", 8080);

        // Register CORS filter for all paths using path patterns
        drogon::app().registerPreHandlingAdvice(
            [](const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& acb, drogon::AdviceChainCallback&& accb) {
                auto corsFilter = std::make_shared<quant_fin::api::CorsFilter>();
                corsFilter->doFilter(req, std::move(acb), std::move(accb));
            }
        );

        API_LOG_INFO("Server configuration loaded successfully");
        API_LOG_INFO("Starting server on port 8080");
        
        app.run();
    } catch (const std::exception &e) {
        API_LOG_CRITICAL("Fatal error during server startup: {}", e.what());
        return 1;
    } catch (...) {
        API_LOG_CRITICAL("Unknown fatal error during server startup");
        return 1;
    }
    return 0;
}
