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
        
        // Load config from the api directory
        app.loadConfigFile("api/config.json");

        // Create the CORS filter
        auto corsFilter = std::make_shared<quant_fin::api::CorsFilter>();
        app.registerFilter(corsFilter);

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
