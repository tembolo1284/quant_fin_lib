#include <drogon/drogon.h>
#include "filters/CorsFilter.h"
#include "utils/Logger.h"
#include "controllers/PricingController.h"
#include <iostream>
#include <filesystem>

int main() {
    try {
        // Get the executable's directory
        std::filesystem::path exe_path = std::filesystem::canonical("/proc/self/exe").parent_path();
        std::filesystem::current_path(exe_path);
        
        // Create logs directory if it doesn't exist
        std::filesystem::create_directories("logs");
        
        // Initialize logger
        quant_fin::api::Logger::init();
        
        API_LOG_INFO("Starting Quantitative Finance API server");
        API_LOG_DEBUG("Initializing server configuration");
        
        // Load configuration
        drogon::app().loadConfigFile("config.json");

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
