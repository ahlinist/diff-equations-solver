#include "equation_solver_controller.hpp"

#include <memory>
#include <string>

#include "../service/equation_solver_service.hpp"
#include "../mapper/solution_mapper.hpp"
#include "../input/input_validator.hpp"
#include "../calc/solution.hpp"

controller::EquationSolverController::EquationSolverController(
        const std::shared_ptr<service::EquationSolverService> equation_solver_service, 
        const std::shared_ptr<mapper::SolutionMapper> solution_mapper,
        const std::shared_ptr<input::InputValidator> input_validator) 
        : equation_solver_service{ equation_solver_service }, solution_mapper{ solution_mapper }, input_validator{ input_validator } {}

std::string controller::EquationSolverControllerImpl::solve_second_order(
        const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    input_validator->validate_second_order(a, b, c, initial_x, initial_x_prime);
    std::shared_ptr<calc::Solution> solution = equation_solver_service->solve_second_order(a, b, c, initial_x, initial_x_prime);
    return solution_mapper->serialize(solution);
};
