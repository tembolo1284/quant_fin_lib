#include "filters/CorsFilter.h"
#include "utils/Logger.h"

namespace quant_fin {
namespace api {

void CorsFilter::doFilter(const drogon::HttpRequestPtr& req,
                        drogon::FilterCallback&& fcb,
                        drogon::FilterChainCallback&& fccb) {
    
    API_LOG_DEBUG("Processing CORS request for path: {}", req->getPath());

    auto resp = drogon::HttpResponse::newHttpResponse();
    
    // Add CORS headers
    resp->addHeader("Access-Control-Allow-Origin", "*");
    resp->addHeader("Access-Control-Allow-Methods", "OPTIONS,GET,POST,HEAD");
    resp->addHeader("Access-Control-Allow-Headers", "x-requested-with,content-type");
    resp->addHeader("Access-Control-Max-Age", "86400");

    // Handle preflight request
    if (req->getMethodString() == "OPTIONS") {
        API_LOG_DEBUG("Handling OPTIONS preflight request");
        resp->setStatusCode(drogon::k204NoContent);
        fcb(resp);
        return;
    }

    // For non-OPTIONS requests, continue with the chain but with CORS headers
    fccb();
}

} // namespace api
} // namespace quant_fin
