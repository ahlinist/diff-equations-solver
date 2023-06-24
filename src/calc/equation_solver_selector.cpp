#include "equation_solver_selector.hpp"

#include <memory>

#include "equation_solver.hpp"

std::shared_ptr<calc::EquationSolver> calc::SecondOrderEquationSolverSelector::select_equation_solver(const long double& discriminant) {
    if (discriminant == 0) {
        return critically_damped_equation_solver;
    } else if (discriminant > 0) {
        return over_damped_equation_solver;
    } else {
        return under_damped_equation_solver;
    }
}
