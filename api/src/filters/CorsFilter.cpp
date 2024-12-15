#include "filters/CorsFilter.h"
#include "utils/Logger.h"

namespace quant_fin {
namespace api {

void CorsFilter::doFilter(const drogon::HttpRequestPtr& req,
                          drogon::FilterCallback&& fcb,
                          drogon::FilterChainCallback&& fccb) {
    API_LOG_DEBUG("CorsFilter invoked for path: {} with method: {}", req->getPath(), req->getMethodString());

    // Add common CORS headers
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->addHeader("Access-Control-Allow-Origin", "http://localhost:3000, http://localhost:5173");
    resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS, PUT, DELETE");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
    resp->addHeader("Access-Control-Allow-Credentials", "true");
    resp->addHeader("Access-Control-Max-Age", "86400");

    // Handle OPTIONS preflight requests
    if (req->getMethodString() == "OPTIONS") {
        API_LOG_DEBUG("Handling OPTIONS preflight request");
        resp->setStatusCode(drogon::k200OK);
        fcb(resp); // Send the response immediately
        return;
    }

    // Add headers for all non-OPTIONS requests and continue the chain
    API_LOG_DEBUG("CORS headers added for non-OPTIONS request");
    fccb(); // Continue the request filter chain
}

} // namespace api
} // namespace quant_fin

