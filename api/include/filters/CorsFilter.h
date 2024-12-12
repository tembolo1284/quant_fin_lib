#ifndef QUANT_FIN_API_CORS_FILTER_H
#define QUANT_FIN_API_CORS_FILTER_H

#include <drogon/HttpFilter.h>

namespace quant_fin {
namespace api {

class CorsFilter : public drogon::HttpFilter<CorsFilter> {
public:
    CorsFilter() {}

    void doFilter(const drogon::HttpRequestPtr& req,
                 drogon::FilterCallback&& fcb,
                 drogon::FilterChainCallback&& fccb) override;
};

} // namespace api
} // namespace quant_fin

#endif // QUANT_FIN_API_CORS_FILTER_H
