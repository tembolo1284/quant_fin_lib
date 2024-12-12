#ifndef QUANT_FIN_API_PRICING_CONTROLLER_H
#define QUANT_FIN_API_PRICING_CONTROLLER_H

#include <drogon/HttpController.h>
#include "pricing/black_scholes.h"
#include "pricing/monte_carlo.h"
#include "pricing/binomial_tree.h"

namespace quant_fin {
namespace api {

class PricingController : public drogon::HttpController<PricingController> {
public:
    METHOD_LIST_BEGIN
    // Use ADD_METHOD_TO for routing
    ADD_METHOD_TO(PricingController::blackScholes, "/api/v1/pricing/black-scholes", drogon::Post);
    ADD_METHOD_TO(PricingController::monteCarlo, "/api/v1/pricing/monte-carlo", drogon::Post);
    ADD_METHOD_TO(PricingController::binomialTree, "/api/v1/pricing/binomial-tree", drogon::Post);
    METHOD_LIST_END

    void blackScholes(const drogon::HttpRequestPtr& req, 
                     std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void monteCarlo(const drogon::HttpRequestPtr& req,
                   std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void binomialTree(const drogon::HttpRequestPtr& req,
                     std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};

} // namespace api
} // namespace quant_fin

#endif // QUANT_FIN_API_PRICING_CONTROLLER_H
