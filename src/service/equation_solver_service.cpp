#include "equation_solver_service.hpp"

#include <memory>

#include "../calc/equation_solver_selector.hpp"
#include "../calc/solution.hpp"

service::EquationSolverService::EquationSolverService(const std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector) 
    : equation_solver_selector{ equation_solver_selector } {}

std::shared_ptr<calc::Solution> service::EquationSolverServiceImpl::solve_second_order(
        const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double discriminant = b * b - 4 * a * c;
    std::shared_ptr<calc::EquationSolver> equation_solver = equation_solver_selector->select_equation_solver(discriminant);
    return equation_solver->solve(discriminant, a, b, c, initial_x, initial_x_prime);
};
