#ifndef EQUATION_SOLVER_REGISTRY_HEADER
#define EQUATION_SOLVER_REGISTRY_HEADER

#include <memory>
#include <string>
#include <unordered_map>

#include "equation_solver.hpp"

namespace calc {
    class EquationSolverSelector {
    public:
        EquationSolverSelector() {}
        explicit EquationSolverSelector(
            std::shared_ptr<calc::EquationSolver> under_damped_equation_solver, 
            std::shared_ptr<calc::EquationSolver> over_damped_equation_solver, 
            std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver) 
            : under_damped_equation_solver{ under_damped_equation_solver }, 
              over_damped_equation_solver{ over_damped_equation_solver }, 
              critically_damped_equation_solver{ critically_damped_equation_solver } {}
        virtual ~EquationSolverSelector() {}
        virtual std::shared_ptr<calc::EquationSolver> select_equation_solver(const long double& discriminant) = 0;
    protected:
        std::shared_ptr<calc::EquationSolver> under_damped_equation_solver;
        std::shared_ptr<calc::EquationSolver> over_damped_equation_solver;
        std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver;
    };

    class SecondOrderEquationSolverSelector : public EquationSolverSelector {
    public:
        using EquationSolverSelector::EquationSolverSelector;
        std::shared_ptr<calc::EquationSolver> select_equation_solver(const long double& discriminant) override;
    };
}

#endif
