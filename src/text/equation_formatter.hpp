#pragma once

#include <string>
#include <memory>

#include "../calc/solution.hpp"

namespace text {
    class EquationFormatter {
    public:
        virtual ~EquationFormatter() {}
        virtual std::string format_second_order_equation(const double& a, const double& b, const double& c) = 0;
        virtual std::string format_second_order_solution(std::shared_ptr<calc::Solution> solution) = 0;
    };

    class SecondOrderEquationFormatter : public EquationFormatter {
    public:
        virtual std::string format_second_order_equation(const double& a, const double& b, const double& c) override;
        virtual std::string format_second_order_solution(std::shared_ptr<calc::Solution> solution) override;
    };
}
