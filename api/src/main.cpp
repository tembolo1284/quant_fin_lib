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
        drogon::app().loadConfigFile("config.json");
        
        // Add filter and listener
        drogon::app()
            .setThreadNum(16)
            .enableRunAsDaemon()
            .enableRelaunchOnError()
            .addListener("0.0.0.0", 8080);

        API_LOG_INFO("Server configuration loaded successfully");
        API_LOG_DEBUG("Starting server...");

        // Run the server
        drogon::app().run();

    } catch (const std::exception &e) {
        API_LOG_CRITICAL("Fatal error during server startup: {}", e.what());
        return 1;
    } catch (...) {
        API_LOG_CRITICAL("Unknown fatal error during server startup");
        return 1;
    }

    return 0;
}
