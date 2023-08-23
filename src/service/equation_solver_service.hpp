#pragma once

#include <memory>

#include "../calc/equation_solver_selector.hpp"
#include "../calc/solution.hpp"
#include "../text/equation_formatter.hpp"
#include "../model/domain_model.hpp"
#include "../calc/function_value_calculator.hpp"

namespace service {
    class EquationSolverService {
    protected:
        std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector;
        std::shared_ptr<text::EquationFormatter> equation_formatter;
        std::shared_ptr<calc::FunctionValueCalculator> function_value_calculator;
    public:
        EquationSolverService() {}
        explicit EquationSolverService(
            const std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector, 
            const std::shared_ptr<text::EquationFormatter> equation_formatter,
            const std::shared_ptr<calc::FunctionValueCalculator> function_value_calculator);
        virtual ~EquationSolverService() {}
        virtual model::SolvedSecondOrderEquation solve_second_order(
            const double& a, const double& b, const double& c, const double& initial_y, const double& initial_y_prime) = 0;
    };

    class EquationSolverServiceImpl : public EquationSolverService {
    public:
        using EquationSolverService::EquationSolverService;
        virtual model::SolvedSecondOrderEquation solve_second_order(
            const double& a, const double& b, const double& c, const double& initial_y, const double& initial_y_prime) override;
    };
}
