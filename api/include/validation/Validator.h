#ifndef QUANT_FIN_API_VALIDATOR_H
#define QUANT_FIN_API_VALIDATOR_H

#include "types/ApiTypes.h"
#include "error/ApiError.h"
#include <json/json.h>

namespace quant_fin {
namespace api {

class Validator {
public:
    static void validateBlackScholesRequest(const Json::Value& json);

private:
    static void validateRequired(const Json::Value& json, const std::string& field);
    static void validatePositive(double value, const std::string& field);
    static void validateRange(double value, double min, double max, const std::string& field);
};

} // namespace api
} // namespace quant_fin

#endif // QUANT_FIN_API_VALIDATOR_H
