#include "filters/CorsFilter.h"
#include "utils/Logger.h"

namespace quant_fin {
namespace api {

void CorsFilter::doFilter(const drogon::HttpRequestPtr& req,
                        drogon::FilterCallback&& fcb,
                        drogon::FilterChainCallback&& fccb) {
    API_LOG_DEBUG("Starting CORS filter for path: {} method: {}", req->getPath(), req->getMethodString());
    API_LOG_DEBUG("Request headers:");
    for (const auto& header : req->getHeaders()) {
        API_LOG_DEBUG("  {}: {}", header.first, header.second);
    }

    // Handle preflight OPTIONS request
    if (req->getMethodString() == "OPTIONS") {
        API_LOG_DEBUG("Processing OPTIONS preflight request");
        auto resp = drogon::HttpResponse::newHttpResponse();
        
        // Add CORS headers for preflight
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "*");
        resp->addHeader("Access-Control-Max-Age", "3600");
        
        // Set 200 OK status
        resp->setStatusCode(drogon::k200OK);
        
        API_LOG_DEBUG("Sending preflight response with headers:");
        for (const auto& header : resp->getHeaders()) {
            API_LOG_DEBUG("  {}: {}", header.first, header.second);
        }
        
        fcb(resp);
        return;
    }

    // For actual request
    API_LOG_DEBUG("Processing actual request");
    
    // Continue with request chain and add CORS headers to the final response
    auto modCallback = [fcb](const drogon::HttpResponsePtr& responsePtr) {
        responsePtr->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        responsePtr->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        responsePtr->addHeader("Access-Control-Allow-Headers", "*");
        fcb(responsePtr);
    };

    fccb();
}

} // namespace api
} // namespace quant_fin
