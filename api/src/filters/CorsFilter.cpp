// CorsFilter.cpp
#include "filters/CorsFilter.h"
#include "utils/Logger.h"

namespace quant_fin {
namespace api {

void CorsFilter::doFilter(const drogon::HttpRequestPtr& req,
                        drogon::FilterCallback&& fcb,
                        drogon::FilterChainCallback&& fccb) {
    API_LOG_DEBUG("Processing CORS request for path: {}", req->getPath());

    if (req->getMethodString() == "OPTIONS") {
        // Handle preflight request
        API_LOG_DEBUG("Handling OPTIONS preflight request");
        auto resp = drogon::HttpResponse::newHttpResponse();
        
        // Add CORS headers for preflight
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        resp->addHeader("Access-Control-Max-Age", "86400");
        
        // Important: Set status 200 for OPTIONS
        resp->setStatusCode(drogon::k200OK);
        fcb(resp);
        return;
    }

    // For non-OPTIONS requests
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
    
    // Continue with the request chain
    fccb();
}

} // namespace api
} // namespace quant_fin
