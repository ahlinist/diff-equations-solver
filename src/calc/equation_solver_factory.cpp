#include "equation_solver_factory.hpp"

#include <memory>

#include "equation_solver.hpp"

std::unique_ptr<calc::EquationSolver> calc::EquationSolverFactory::create_equation_solver(const long double& discriminant) {
    if (discriminant == 0) {
        return std::make_unique<calc::CriticallyDampedEquationSolver>();
    } else if (discriminant > 0) {
        return std::make_unique<calc::OverDampedEquationSolver>();
    } else {
        return std::make_unique<calc::UnderDampedEquationSolver>();
    }
}
