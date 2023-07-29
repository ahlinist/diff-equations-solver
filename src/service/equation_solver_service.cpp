#include "equation_solver_service.hpp"

#include <memory>

#include "../calc/equation_solver_selector.hpp"
#include "../calc/solution.hpp"
#include "../text/equation_formatter.hpp"
#include "../model/domain_model.hpp"
#include "../calc/function_value_calculator.hpp"

service::EquationSolverService::EquationSolverService(
    const std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector, 
    const std::shared_ptr<text::EquationFormatter> equation_formatter,
    const std::shared_ptr<calc::FunctionValueCalculator> function_value_calculator)
    : equation_solver_selector{ equation_solver_selector }, equation_formatter{ equation_formatter }, function_value_calculator{ function_value_calculator } {}

model::SolvedSecondOrderEquation service::EquationSolverServiceImpl::solve_second_order(
        const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double discriminant = b * b - 4 * a * c;
    std::shared_ptr<calc::EquationSolver> equation_solver = equation_solver_selector->select_equation_solver(discriminant);
    std::shared_ptr<calc::Solution> solution =  equation_solver->solve(discriminant, a, b, c, initial_x, initial_x_prime);
    std::string initial_equation = equation_formatter->format_second_order_equation(a, b, c);
    std::string solution_equation = equation_formatter->format_second_order_solution(solution);
    std::vector<model::FunctionDataPoint> function_data_points = function_value_calculator->calculate_function_values(solution);
    model::SolvedSecondOrderEquation solved_equation{ initial_equation, solution_equation, function_data_points };
    return solved_equation;
};
