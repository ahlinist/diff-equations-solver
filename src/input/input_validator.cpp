#include "input_validator.hpp"

#include <string>
#include <stdexcept>

void input::InputValidatorImpl::validate_second_order(const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    std::string result{};

    if (initial_x == 0 and initial_x_prime == 0) {
        result += "Initial conditions x and x' should not be 0 simultaneously.\n";
    }

    if (a < 0 or b < 0 or c < 0) {
        result += "a, b and c need to be greater than 0.\n";
    }

    if (result.size()) {
        throw std::invalid_argument(result);
    }
}
