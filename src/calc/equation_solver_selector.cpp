#include "equation_solver_selector.hpp"

#include <memory>

#include "equation_solver.hpp"

calc::EquationSolverSelector::EquationSolverSelector(
            std::shared_ptr<calc::EquationSolver> under_damped_equation_solver, 
            std::shared_ptr<calc::EquationSolver> over_damped_equation_solver, 
            std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver) 
            : under_damped_equation_solver{ under_damped_equation_solver }, 
              over_damped_equation_solver{ over_damped_equation_solver }, 
              critically_damped_equation_solver{ critically_damped_equation_solver } {}

std::shared_ptr<calc::EquationSolver> calc::SecondOrderEquationSolverSelector::select_equation_solver(const long double& discriminant) {
    if (discriminant == 0) {
        return critically_damped_equation_solver;
    } else if (discriminant > 0) {
        return over_damped_equation_solver;
    } else {
        return under_damped_equation_solver;
    }
}
