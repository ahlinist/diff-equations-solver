#include <memory>

#include "../libs/httplib.h"

#include "text/equation_formatter.hpp"
#include "calc/equation_solver_selector.hpp"
#include "service/equation_solver_service.hpp"
#include "controller/equation_solver_controller.hpp"
#include "router/equation_solver_router.hpp"
#include "mapper/solution_mapper.hpp"
#include "input/input_validator.hpp"

int main() {
    std::shared_ptr<text::EquationFormatter> equation_formatter = std::make_shared<text::SecondOrderEquationFormatter>(); 
    std::shared_ptr<calc::EquationSolver> under_damped_equation_solver = std::make_shared<calc::UnderDampedEquationSolver>();
    std::shared_ptr<calc::EquationSolver> over_damped_equation_solver = std::make_shared<calc::OverDampedEquationSolver>();
    std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver = std::make_shared<calc::CriticallyDampedEquationSolver>();
    std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector = std::make_shared<calc::SecondOrderEquationSolverSelector>(
        under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver);
    std::shared_ptr<calc::FunctionValueCalculator> function_value_calculator = std::make_shared<calc::SecondOrderFunctionValueCalculator>();
    std::shared_ptr<service::EquationSolverService> equation_solver_service = 
        std::make_shared<service::EquationSolverServiceImpl>(equation_solver_selector, equation_formatter, function_value_calculator);
    std::shared_ptr<mapper::SolutionMapper> solution_mapper = std::make_shared<mapper::SolutionMapperImpl>();
    std::shared_ptr<input::InputValidator> input_validator = std::make_shared<input::InputValidatorImpl>();
    std::shared_ptr<controller::EquationSolverController> equation_solver_controller 
        = std::make_shared<controller::EquationSolverControllerImpl>(equation_solver_service, solution_mapper, input_validator);

    std::shared_ptr<httplib::Server> server = std::make_shared<httplib::Server>();
    router::EquationSolverRouter equation_solver_router{ server, equation_solver_controller };
    equation_solver_router.register_routes();

    //TODO: separate web-server and app logic
    std::cout << "Starting up a server..." << std::endl;
    server->listen("0.0.0.0", 8080);
}
