#include "types/ApiTypes.h"
#include "error/ApiError.h"

namespace quant_fin {
namespace api {

BlackScholesRequest BlackScholesRequest::fromJson(const Json::Value& json) {
    BlackScholesRequest request;
    
    if (!json.isMember("spot_price") || !json["spot_price"].isDouble()) {
        throw ApiError("Missing or invalid spot_price");
    }
    request.spot_price = json["spot_price"].asDouble();

    if (!json.isMember("strike_price") || !json["strike_price"].isDouble()) {
        throw ApiError("Missing or invalid strike_price");
    }
    request.strike_price = json["strike_price"].asDouble();

    if (!json.isMember("risk_free_rate") || !json["risk_free_rate"].isDouble()) {
        throw ApiError("Missing or invalid risk_free_rate");
    }
    request.risk_free_rate = json["risk_free_rate"].asDouble();

    if (!json.isMember("time_to_maturity") || !json["time_to_maturity"].isDouble()) {
        throw ApiError("Missing or invalid time_to_maturity");
    }
    request.time_to_maturity = json["time_to_maturity"].asDouble();

    if (!json.isMember("volatility") || !json["volatility"].isDouble()) {
        throw ApiError("Missing or invalid volatility");
    }
    request.volatility = json["volatility"].asDouble();

    if (!json.isMember("is_call") || !json["is_call"].isBool()) {
        throw ApiError("Missing or invalid is_call");
    }
    request.is_call = json["is_call"].asBool();

    return request;
}

MonteCarloRequest MonteCarloRequest::fromJson(const Json::Value& json) {
    MonteCarloRequest request;
    
    // Base parameters
    if (!json.isMember("spot_price") || !json["spot_price"].isDouble()) {
        throw ApiError("Missing or invalid spot_price");
    }
    request.spot_price = json["spot_price"].asDouble();

    if (!json.isMember("strike_price") || !json["strike_price"].isDouble()) {
        throw ApiError("Missing or invalid strike_price");
    }
    request.strike_price = json["strike_price"].asDouble();

    if (!json.isMember("risk_free_rate") || !json["risk_free_rate"].isDouble()) {
        throw ApiError("Missing or invalid risk_free_rate");
    }
    request.risk_free_rate = json["risk_free_rate"].asDouble();

    if (!json.isMember("time_to_maturity") || !json["time_to_maturity"].isDouble()) {
        throw ApiError("Missing or invalid time_to_maturity");
    }
    request.time_to_maturity = json["time_to_maturity"].asDouble();

    if (!json.isMember("volatility") || !json["volatility"].isDouble()) {
        throw ApiError("Missing or invalid volatility");
    }
    request.volatility = json["volatility"].asDouble();

    if (!json.isMember("is_call") || !json["is_call"].isBool()) {
        throw ApiError("Missing or invalid is_call");
    }
    request.is_call = json["is_call"].asBool();

    // Monte Carlo specific parameters
    if (!json.isMember("num_simulations") || !json["num_simulations"].isInt()) {
        throw ApiError("Missing or invalid num_simulations");
    }
    request.num_simulations = json["num_simulations"].asInt();

    if (!json.isMember("num_steps") || !json["num_steps"].isInt()) {
        throw ApiError("Missing or invalid num_steps");
    }
    request.num_steps = json["num_steps"].asInt();

    return request;
}

BinomialTreeRequest BinomialTreeRequest::fromJson(const Json::Value& json) {
    BinomialTreeRequest request;
    
    // Base parameters
    if (!json.isMember("spot_price") || !json["spot_price"].isDouble()) {
        throw ApiError("Missing or invalid spot_price");
    }
    request.spot_price = json["spot_price"].asDouble();

    if (!json.isMember("strike_price") || !json["strike_price"].isDouble()) {
        throw ApiError("Missing or invalid strike_price");
    }
    request.strike_price = json["strike_price"].asDouble();

    if (!json.isMember("risk_free_rate") || !json["risk_free_rate"].isDouble()) {
        throw ApiError("Missing or invalid risk_free_rate");
    }
    request.risk_free_rate = json["risk_free_rate"].asDouble();

    if (!json.isMember("time_to_maturity") || !json["time_to_maturity"].isDouble()) {
        throw ApiError("Missing or invalid time_to_maturity");
    }
    request.time_to_maturity = json["time_to_maturity"].asDouble();

    if (!json.isMember("volatility") || !json["volatility"].isDouble()) {
        throw ApiError("Missing or invalid volatility");
    }
    request.volatility = json["volatility"].asDouble();

    if (!json.isMember("is_call") || !json["is_call"].isBool()) {
        throw ApiError("Missing or invalid is_call");
    }
    request.is_call = json["is_call"].asBool();

    // Binomial Tree specific parameters
    if (!json.isMember("num_steps") || !json["num_steps"].isInt()) {
        throw ApiError("Missing or invalid num_steps");
    }
    request.num_steps = json["num_steps"].asInt();

    return request;
}

} // namespace api
} // namespace quant_fin
