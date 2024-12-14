#include "controllers/PricingController.h"
#include "types/ApiTypes.h"
#include "validation/Validator.h"
#include "error/ApiError.h"
#include "constants/ApiConstants.h"
#include "utils/Logger.h"
#include <drogon/drogon.h>
#include <iomanip>
#include <sstream>

namespace quant_fin {
namespace api {

// Helper function to format double to string with specified precision
std::string formatDouble(double value, int precision = 6) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    std::string str = oss.str();
    // Remove trailing zeros after decimal point
    size_t decimal_pos = str.find('.');
    if (decimal_pos != std::string::npos) {
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        if (str.back() == '.') {
            str.pop_back();
        }
    }
    return str;
}

void PricingController::blackScholes(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    
    API_LOG_DEBUG("Received Black-Scholes pricing request");
    
    try {
        auto json = req->getJsonObject();
        if (!json) {
            API_LOG_WARN("Invalid JSON in request body");
            auto resp = drogon::HttpResponse::newHttpJsonResponse(
                ApiResponse::error("Invalid request format")
            );
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

        Json::Value response;
        response["success"] = true;
        response["message"] = "Option price calculated successfully";

        Json::Value resultData;
        resultData["price"] = formatDouble(price, 4);
        
        Json::Value params;
        params["spot_price"] = formatDouble(request.spot_price, 2);
        params["strike_price"] = formatDouble(request.strike_price, 2);
        params["risk_free_rate"] = formatDouble(request.risk_free_rate, 3);
        params["time_to_maturity"] = formatDouble(request.time_to_maturity, 2);
        params["volatility"] = formatDouble(request.volatility, 2);
        params["is_call"] = request.is_call;
        
        resultData["input_params"] = params;
        response["data"] = resultData;

        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k200OK);
        resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        writer["precision"] = 4;
        std::string output = Json::writeString(writer, response);
        
        resp->setBody(output);
        callback(resp);

    } catch (const std::exception& e) {
        API_LOG_ERROR("Error in Black-Scholes calculation: {}", e.what());
        auto error_response = Json::Value();
        error_response["success"] = false;
        error_response["message"] = e.what();
        error_response["data"] = Json::Value(Json::nullValue);

        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        std::string output = Json::writeString(writer, error_response);
        
        resp->setBody(output);
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
            auto resp = drogon::HttpResponse::newHttpJsonResponse(
                ApiResponse::error("Invalid request format")
            );
            resp->setStatusCode(drogon::k400BadRequest);
            callback(resp);
            return;
        }

        API_LOG_DEBUG("Validating request parameters");
        auto request = MonteCarloRequest::fromJson(*json);

        API_LOG_INFO("Calculating Monte Carlo price with parameters: spot={}, strike={}, r={}, t={}, vol={}, is_call={}, sims={}, steps={}",
                request.spot_price, request.strike_price, request.risk_free_rate,
                request.time_to_maturity, request.volatility, request.is_call,
                request.num_simulations, request.num_steps);

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

        Json::Value response;
        response["success"] = true;
        response["message"] = "Option price calculated successfully";

        Json::Value resultData;
        resultData["price"] = formatDouble(price, 4);
        
        Json::Value params;
        params["spot_price"] = formatDouble(request.spot_price, 2);
        params["strike_price"] = formatDouble(request.strike_price, 2);
        params["risk_free_rate"] = formatDouble(request.risk_free_rate, 3);
        params["time_to_maturity"] = formatDouble(request.time_to_maturity, 2);
        params["volatility"] = formatDouble(request.volatility, 2);
        params["is_call"] = request.is_call;
        params["num_simulations"] = request.num_simulations;
        params["num_steps"] = request.num_steps;
        
        resultData["input_params"] = params;
        response["data"] = resultData;

        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k200OK);
        resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        writer["precision"] = 4;
        std::string output = Json::writeString(writer, response);
        
        resp->setBody(output);
        callback(resp);

    } catch (const std::exception& e) {
        API_LOG_ERROR("Error in Monte Carlo calculation: {}", e.what());
        auto error_response = Json::Value();
        error_response["success"] = false;
        error_response["message"] = e.what();
        error_response["data"] = Json::Value(Json::nullValue);

        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        std::string output = Json::writeString(writer, error_response);
        
        resp->setBody(output);
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
            auto resp = drogon::HttpResponse::newHttpJsonResponse(
                ApiResponse::error("Invalid request format")
            );
            resp->setStatusCode(drogon::k400BadRequest);
            callback(resp);
            return;
        }

        API_LOG_DEBUG("Validating request parameters");
        auto request = BinomialTreeRequest::fromJson(*json);

        API_LOG_INFO("Calculating Binomial Tree price with parameters: spot={}, strike={}, r={}, t={}, vol={}, is_call={}, steps={}",
                request.spot_price, request.strike_price, request.risk_free_rate,
                request.time_to_maturity, request.volatility, request.is_call,
                request.num_steps);

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

        Json::Value response;
        response["success"] = true;
        response["message"] = "Option price calculated successfully";

        Json::Value resultData;
        resultData["price"] = formatDouble(price, 4);
        
        Json::Value params;
        params["spot_price"] = formatDouble(request.spot_price, 2);
        params["strike_price"] = formatDouble(request.strike_price, 2);
        params["risk_free_rate"] = formatDouble(request.risk_free_rate, 3);
        params["time_to_maturity"] = formatDouble(request.time_to_maturity, 2);
        params["volatility"] = formatDouble(request.volatility, 2);
        params["is_call"] = request.is_call;
        params["num_steps"] = request.num_steps;
        
        resultData["input_params"] = params;
        response["data"] = resultData;

        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k200OK);
        resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        writer["precision"] = 4;
        std::string output = Json::writeString(writer, response);
        
        resp->setBody(output);
        callback(resp);

    } catch (const std::exception& e) {
        API_LOG_ERROR("Error in Binomial Tree calculation: {}", e.what());
        auto error_response = Json::Value();
        error_response["success"] = false;
        error_response["message"] = e.what();
        error_response["data"] = Json::Value(Json::nullValue);

        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "    ";
        std::string output = Json::writeString(writer, error_response);
        
        resp->setBody(output);
        callback(resp);
    }
}

} // namespace api
} // namespace quant_fin
