#pragma once

#include <memory>
#include <vector>

#include "solution.hpp"
#include "../model/domain_model.hpp"

namespace calc {
    class FunctionValueCalculator {
    protected:
        virtual long double calculate_max_amplitude(std::shared_ptr<calc::Solution> solution) = 0;
        virtual long double calculate_decay_time(std::shared_ptr<calc::Solution> solution) = 0;
    public:
        virtual ~FunctionValueCalculator() {}
        virtual long double calculate_value_at_time(std::shared_ptr<calc::Solution> solution, const long double& time) = 0;
        virtual std::vector<model::FunctionDataPoint> calculate_function_values(std::shared_ptr<calc::Solution> solution) = 0;
    };

    class SecondOrderFunctionValueCalculator : public FunctionValueCalculator {
    protected:
        virtual long double calculate_max_amplitude(std::shared_ptr<calc::Solution> solution) override;
        virtual long double calculate_decay_time(std::shared_ptr<calc::Solution> solution) override;
    public:
        virtual long double calculate_value_at_time(std::shared_ptr<calc::Solution> solution, const long double& time) override;
        virtual std::vector<model::FunctionDataPoint> calculate_function_values(std::shared_ptr<calc::Solution> solution) override;
    };
}
