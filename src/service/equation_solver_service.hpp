#pragma once

#include <memory>

#include "../input/input_formatter.hpp"
#include "../calc/equation_solver_selector.hpp"
#include "../calc/solution.hpp"

namespace service {
    class EquationSolverService {
    protected:
        std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector;
    public:
        explicit EquationSolverService(const std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector);
        virtual std::shared_ptr<calc::Solution> solve_second_level(
            const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) = 0;
    };

    class EquationSolverServiceImpl : public EquationSolverService {
    public:
        using EquationSolverService::EquationSolverService;
        std::shared_ptr<calc::Solution> solve_second_level(
            const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };
}
