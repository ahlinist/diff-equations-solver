#pragma once

#include <memory>

#include "solution.hpp"

namespace calc {
    class FunctionValueCalculator {
    public:
        virtual long double calculate_value_at(std::shared_ptr<calc::Solution> solution, const double& time) = 0;
    };

    class SecondOrderFunctionValueCalculator : public FunctionValueCalculator {
    public:
        long double calculate_value_at(std::shared_ptr<calc::Solution> solution, const double& time) override;
    };
}
