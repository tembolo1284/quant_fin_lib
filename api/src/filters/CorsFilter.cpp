#include "filters/CorsFilter.h"
#include "utils/Logger.h"

namespace quant_fin {
namespace api {

void CorsFilter::doFilter(const drogon::HttpRequestPtr& req,
                        drogon::FilterCallback&& fcb,
                        drogon::FilterChainCallback&& fccb) {
    
    API_LOG_DEBUG("Processing CORS request for path: {}", req->getPath());

    if (req->getMethod() == drogon::HttpMethod::Options) {
        API_LOG_DEBUG("Handling OPTIONS request with CORS headers");
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::HttpStatusCode::k204NoContent);
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        resp->addHeader("Access-Control-Max-Age", "86400");
        fcb(resp);
        return;
    }

    // Add CORS headers for non-OPTIONS requests
    req->addHeader("Access-Control-Allow-Origin", "*");
    API_LOG_DEBUG("Added CORS headers to request");

    // Continue with the next filter or handler
    fccb();
}

} // namespace api
} // namespace quant_fin
