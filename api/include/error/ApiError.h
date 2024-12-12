#ifndef QUANT_FIN_API_ERROR_H
#define QUANT_FIN_API_ERROR_H

#include <stdexcept>
#include <string>

namespace quant_fin {
namespace api {

class ApiError : public std::runtime_error {
public:
    explicit ApiError(const std::string& message, int status_code = 400)
        : std::runtime_error(message), status_code_(status_code) {}

    int statusCode() const { return status_code_; }

private:
    int status_code_;
};

} // namespace api
} // namespace quant_fin

#endif // QUANT_FIN_API_ERROR_H
