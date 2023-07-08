#include "input_validator.hpp"

#include <stdexcept>

void input::InputValidatorImpl::validate_second_order(const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    if (initial_x == 0 and initial_x_prime == 0) {
        throw std::invalid_argument("Initial conditions x and x' should not be 0 simultaneously.");
    }

    //TODO: add validation for negative values
}
