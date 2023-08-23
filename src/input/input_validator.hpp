#pragma once

namespace input {
    class InputValidator {
    public:
        virtual ~InputValidator() {}
        virtual void validate_second_order(const double& a, const double& b, const double& c, const double& initial_y, const double& initial_y_prime) = 0;
    };

    class InputValidatorImpl : public InputValidator {
    public:
        void validate_second_order(const double& a, const double& b, const double& c, const double& initial_y, const double& initial_y_prime) override;
    };
}
