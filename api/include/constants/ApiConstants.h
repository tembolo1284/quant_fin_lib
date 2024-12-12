#ifndef QUANT_FIN_API_CONSTANTS_H
#define QUANT_FIN_API_CONSTANTS_H

#include <string>

namespace quant_fin {
namespace api {
namespace constants {

// API Versions
const char* const API_VERSION = "v1";
const char* const API_BASE_PATH = "/api";

// Endpoint paths
namespace endpoints {
    inline std::string getVersionPath() {
        return std::string(API_BASE_PATH) + "/" + API_VERSION;
    }

    inline std::string blackScholes() {
        return getVersionPath() + "/pricing/black-scholes";
    }
} // namespace endpoints

// Error Messages
namespace errors {
    const char* const INVALID_REQUEST = "Invalid request format";
    const char* const MISSING_FIELD = "Missing required field: ";
    const char* const INVALID_VALUE = "Invalid value for field: ";
    const char* const INTERNAL_ERROR = "Internal server error";
} // namespace errors

} // namespace constants
} // namespace api
} // namespace quant_fin

#endif // QUANT_FIN_API_CONSTANTS_H
