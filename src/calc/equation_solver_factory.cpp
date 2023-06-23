#include "equation_solver_factory.hpp"

#include <memory>

#include "equation_solver.hpp"

std::shared_ptr<calc::EquationSolver> calc::SecondOrderEquationSolverFactory::create_equation_solver(const long double& discriminant) {
    if (discriminant == 0) {
        return std::make_shared<calc::CriticallyDampedEquationSolver>();
    } else if (discriminant > 0) {
        return std::make_shared<calc::OverDampedEquationSolver>();
    } else {
        return std::make_shared<calc::UnderDampedEquationSolver>();
    }
}
