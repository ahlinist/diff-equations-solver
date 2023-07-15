#pragma once

#include <string>

#include "../calc/solution.hpp"

namespace text {
    class EquationFormatter {
    public:
        virtual ~EquationFormatter() {}
        virtual std::string format_second_order(const double& a, const double& b, const double& c) = 0;
        virtual std::string format_under_damped_result(
            const long double& first_root_real_part, const long double& first_root_imaginary_part, const long double& coefficient_a, const long double& coefficient_b) = 0;
        virtual std::string format_over_damped_result(
            const long double& first_root_real_part, const long double& second_root_real_part, const long double& coefficient_a, const long double& coefficient_b) = 0;
        virtual std::string format_critically_damped_result(
            const long double& first_root_real_part, const long double& coefficient_a, const long double& coefficient_b) = 0;
    };

    class SecondOrderEquationFormatter : public EquationFormatter {
    public:
        std::string format_second_order(const double& a, const double& b, const double& c) override;
        std::string format_under_damped_result(
            const long double& first_root_real_part, const long double& first_root_imaginary_part, const long double& coefficient_a, const long double& coefficient_b) override;
        std::string format_over_damped_result(
            const long double& first_root_real_part, const long double& second_root_real_part, const long double& coefficient_a, const long double& coefficient_b) override;
        std::string format_critically_damped_result(
            const long double& first_root_real_part, const long double& coefficient_a, const long double& coefficient_b) override;
    };
}
