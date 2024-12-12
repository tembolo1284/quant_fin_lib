#include "controllers/PricingController.h"
#include "types/ApiTypes.h"
#include "validation/Validator.h"
#include "error/ApiError.h"
#include "constants/ApiConstants.h"
#include "utils/Logger.h"
#include <drogon/drogon.h>

namespace quant_fin {
namespace api {

void PricingController::blackScholes(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    
    API_LOG_DEBUG("Received Black-Scholes pricing request");
    Json::Value jsonResponse;
    
    try {
        auto json = req->getJsonObject();
        if (!json) {
            API_LOG_WARN("Invalid JSON in request body");
            auto resp = drogon::HttpResponse::newHttpJsonResponse(ApiResponse::error("Invalid request format"));
            resp->setStatusCode(drogon::k400BadRequest);
            callback(resp);
            return;
        }

        API_LOG_DEBUG("Validating request parameters");
        auto request = BlackScholesRequest::fromJson(*json);

        API_LOG_INFO("Calculating Black-Scholes price with parameters: spot={}, strike={}, r={}, t={}, vol={}, is_call={}",
                request.spot_price, request.strike_price, request.risk_free_rate,
                request.time_to_maturity, request.volatility, request.is_call);

        double price = black_scholes_price(
            request.spot_price,
            request.strike_price,
            request.risk_free_rate,
            request.time_to_maturity,
            request.volatility,
            request.is_call
        );

        API_LOG_INFO("Black-Scholes calculation completed. Result: {}", price);

        Json::Value resultData;
        resultData["price"] = price;
        resultData["input_params"] = request.toJson();
        
        auto resp = drogon::HttpResponse::newHttpJsonResponse(
            ApiResponse::success("Option price calculated successfully", resultData)
        );
        resp->setStatusCode(drogon::k200OK);
        callback(resp);

    } catch (const std::exception& e) {
        API_LOG_ERROR("Error in Black-Scholes calculation: {}", e.what());
        auto resp = drogon::HttpResponse::newHttpJsonResponse(ApiResponse::error(e.what()));
        resp->setStatusCode(drogon::k400BadRequest);
        callback(resp);
    }
}

void PricingController::monteCarlo(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    
    API_LOG_DEBUG("Received Monte Carlo pricing request");
    
    try {
        auto json = req->getJsonObject();
        if (!json) {
            API_LOG_WARN("Invalid JSON in request body");
            auto resp = drogon::HttpResponse::newHttpJsonResponse(ApiResponse::error("Invalid request format"));
            resp->setStatusCode(drogon::k400BadRequest);
            callback(resp);
            return;
        }

        API_LOG_DEBUG("Validating request parameters");
        auto request = MonteCarloRequest::fromJson(*json);

        API_LOG_INFO("Calculating Monte Carlo price");

        double price = monte_carlo_price(
            request.spot_price,
            request.strike_price,
            request.risk_free_rate,
            request.time_to_maturity,
            request.volatility,
            request.is_call,
            request.num_simulations,
            request.num_steps
        );

        API_LOG_INFO("Monte Carlo calculation completed. Result: {}", price);

        Json::Value resultData;
        resultData["price"] = price;
        resultData["input_params"] = request.toJson();
        
        auto resp = drogon::HttpResponse::newHttpJsonResponse(
            ApiResponse::success("Option price calculated successfully", resultData)
        );
        resp->setStatusCode(drogon::k200OK);
        callback(resp);

    } catch (const std::exception& e) {
        API_LOG_ERROR("Error in Monte Carlo calculation: {}", e.what());
        auto resp = drogon::HttpResponse::newHttpJsonResponse(ApiResponse::error(e.what()));
        resp->setStatusCode(drogon::k400BadRequest);
        callback(resp);
    }
}

void PricingController::binomialTree(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    
    API_LOG_DEBUG("Received Binomial Tree pricing request");
    
    try {
        auto json = req->getJsonObject();
        if (!json) {
            API_LOG_WARN("Invalid JSON in request body");
            auto resp = drogon::HttpResponse::newHttpJsonResponse(ApiResponse::error("Invalid request format"));
            resp->setStatusCode(drogon::k400BadRequest);
            callback(resp);
            return;
        }

        API_LOG_DEBUG("Validating request parameters");
        auto request = BinomialTreeRequest::fromJson(*json);

        API_LOG_INFO("Calculating Binomial Tree price");

        double price = binomial_tree_price(
            request.spot_price,
            request.strike_price,
            request.risk_free_rate,
            request.time_to_maturity,
            request.volatility,
            request.is_call,
            request.num_steps
        );

        API_LOG_INFO("Binomial Tree calculation completed. Result: {}", price);

        Json::Value resultData;
        resultData["price"] = price;
        resultData["input_params"] = request.toJson();
        
        auto resp = drogon::HttpResponse::newHttpJsonResponse(
            ApiResponse::success("Option price calculated successfully", resultData)
        );
        resp->setStatusCode(drogon::k200OK);
        callback(resp);

    } catch (const std::exception& e) {
        API_LOG_ERROR("Error in Binomial Tree calculation: {}", e.what());
        auto resp = drogon::HttpResponse::newHttpJsonResponse(ApiResponse::error(e.what()));
        resp->setStatusCode(drogon::k400BadRequest);
        callback(resp);
    }
}

} // namespace api
} // namespace quant_fin
