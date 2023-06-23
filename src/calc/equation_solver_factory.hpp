#ifndef EQUATION_SOLVER_FACTORY_HEADER
#define EQUATION_SOLVER_FACTORY_HEADER

#include <memory>

#include "equation_solver.hpp"

namespace calc {
    class EquationSolverFactory {
    public:
        virtual std::shared_ptr<calc::EquationSolver> create_equation_solver(const long double& discriminant) = 0;
    };

    class SecondOrderEquationSolverFactory : public EquationSolverFactory {
    public:
        std::shared_ptr<calc::EquationSolver> create_equation_solver(const long double& discriminant) override;
    };
}

#endif
