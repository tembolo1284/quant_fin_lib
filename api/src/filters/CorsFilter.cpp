// CorsFilter.cpp
#include "filters/CorsFilter.h"
#include "utils/Logger.h"

namespace quant_fin {
namespace api {

void CorsFilter::doFilter(const drogon::HttpRequestPtr& req,
                        drogon::FilterCallback&& fcb,
                        drogon::FilterChainCallback&& fccb) {
    API_LOG_DEBUG("Processing CORS request for path: {}", req->getPath());

    // Create response for handling CORS
    auto resp = drogon::HttpResponse::newHttpResponse();
    
    // Add CORS headers matching your config
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    resp->addHeader("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type,Authorization");
    resp->addHeader("Access-Control-Max-Age", "86400");

    // Handle preflight request
    if (req->getMethodString() == "OPTIONS") {
        API_LOG_DEBUG("Handling OPTIONS preflight request");
        resp->setStatusCode(drogon::k204NoContent);
        fcb(resp);
        return;
    }

    // For non-OPTIONS requests, add CORS headers to the response
    req->addHeader("Access-Control-Allow-Origin", "http://localhost:3000");
    req->addHeader("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
    req->addHeader("Access-Control-Allow-Headers", "Content-Type,Authorization");
    req->addHeader("Access-Control-Max-Age", "86400");

    // Continue with the request chain
    fccb();
}

} // namespace api
} // namespace quant_fin
