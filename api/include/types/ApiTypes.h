#ifndef QUANT_FIN_API_TYPES_H
#define QUANT_FIN_API_TYPES_H

#include <string>
#include <json/json.h>

namespace quant_fin {
namespace api {

// Base struct for common option parameters
struct OptionRequestBase {
    double spot_price;
    double strike_price;
    double risk_free_rate;
    double time_to_maturity;
    double volatility;
    bool is_call;

    virtual Json::Value toJson() const {
        Json::Value json;
        json["spot_price"] = spot_price;
        json["strike_price"] = strike_price;
        json["risk_free_rate"] = risk_free_rate;
        json["time_to_maturity"] = time_to_maturity;
        json["volatility"] = volatility;
        json["is_call"] = is_call;
        return json;
    }
};

struct BlackScholesRequest : public OptionRequestBase {
    static BlackScholesRequest fromJson(const Json::Value& json);
};

struct MonteCarloRequest : public OptionRequestBase {
    int num_simulations;
    int num_steps;

    Json::Value toJson() const override {
        Json::Value json = OptionRequestBase::toJson();
        json["num_simulations"] = num_simulations;
        json["num_steps"] = num_steps;
        return json;
    }

    static MonteCarloRequest fromJson(const Json::Value& json);
};

struct BinomialTreeRequest : public OptionRequestBase {
    int num_steps;

    Json::Value toJson() const override {
        Json::Value json = OptionRequestBase::toJson();
        json["num_steps"] = num_steps;
        return json;
    }

    static BinomialTreeRequest fromJson(const Json::Value& json);
};

class ApiResponse {
public:
    static Json::Value success(const std::string& message, const Json::Value& data) {
        Json::Value response;
        response["success"] = true;
        response["message"] = message;
        response["data"] = data;
        return response;
    }

    static Json::Value error(const std::string& message) {
        Json::Value response;
        response["success"] = false;
        response["message"] = message;
        response["data"] = Json::Value(Json::nullValue);
        return response;
    }
};

} // namespace api
} // namespace quant_fin

#endif // QUANT_FIN_API_TYPES_H
