#include "equation_solver_controller.hpp"

#include <memory>
#include <string>

#include "../service/equation_solver_service.hpp"
#include "../mapper/solution_mapper.hpp"
#include "../input/input_validator.hpp"
#include "../calc/solution.hpp"
#include "../model/domain_model.hpp"

controller::EquationSolverController::EquationSolverController(
        const std::shared_ptr<service::EquationSolverService> equation_solver_service, 
        const std::shared_ptr<mapper::SolutionMapper> solution_mapper,
        const std::shared_ptr<input::InputValidator> input_validator) 
        : equation_solver_service{ equation_solver_service }, solution_mapper{ solution_mapper }, input_validator{ input_validator } {}

std::string controller::EquationSolverControllerImpl::solve_second_order(
        const double& a, const double& b, const double& c, const double& initial_y, const double& initial_y_prime) {
    input_validator->validate_second_order(a, b, c, initial_y, initial_y_prime);
    model::SolvedSecondOrderEquation solved_equation = equation_solver_service->solve_second_order(a, b, c, initial_y, initial_y_prime);
    return solution_mapper->serialize(solved_equation);

    //TODO: to check how to return string reference instead of copying a string
};
