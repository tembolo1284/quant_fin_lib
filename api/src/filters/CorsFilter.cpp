#include "filters/CorsFilter.h"
#include "utils/Logger.h"

namespace quant_fin {
namespace api {

void CorsFilter::doFilter(const drogon::HttpRequestPtr& req,
                        drogon::FilterCallback&& fcb,
                        drogon::FilterChainCallback&& fccb) {
    API_LOG_DEBUG("Starting CORS filter for path: {} method: {}", req->getPath(), req->getMethodString());
    
    // Create response for CORS headers
    auto resp = drogon::HttpResponse::newHttpResponse();
    
    // Handle preflight OPTIONS request
    if (req->getMethodString() == "OPTIONS") {
        API_LOG_DEBUG("Processing OPTIONS preflight request");
        
        // Essential CORS headers
        resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        
        // Set 200 OK status explicitly
        resp->setStatusCode(drogon::k200OK);
        resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
        
        // Send the response immediately for OPTIONS
        fcb(resp);
        return;
    }

    // For non-OPTIONS requests
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    
    // Continue with the normal request chain
    fccb();
}

} // namespace api
} // namespace quant_fin
