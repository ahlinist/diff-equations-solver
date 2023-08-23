#include "input_validator.hpp"

#include <string>
#include <stdexcept>

void input::InputValidatorImpl::validate_second_order(const double& a, const double& b, const double& c, const double& initial_y, const double& initial_y_prime) {
    std::string result{};

    if (initial_y == 0 and initial_y_prime == 0) {
        result += "Initial conditions y and y' should not be 0 simultaneously.\n";
    }

    if (a <= 0) {
        result += "a needs to be greater than 0.\n";
    }

    if (b < 0 or c < 0) {
        result += "b and c need to be greater than or equal 0.\n";
    }

    if (result.size()) {
        throw std::invalid_argument(result);
    }
}
