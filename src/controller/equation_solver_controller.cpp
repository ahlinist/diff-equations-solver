#include "equation_solver_controller.hpp"

#include <memory>
#include <string>

#include "../service/equation_solver_service.hpp"
#include "../../libs/httplib.h"

controller::EquationSolverController::EquationSolverController(
    const std::shared_ptr<httplib::Server> server, const std::shared_ptr<service::EquationSolverService> equation_solver_service) 
        : server{ server }, equation_solver_service{ equation_solver_service } {}

void controller::EquationSolverControllerImpl::enable() {

    //TODO: decouple controller and routing logic
    server->Get("/solution", [this](const httplib::Request& request, httplib::Response& response) {
        double a = std::stod(request.get_param_value("a"));
        double b = std::stod(request.get_param_value("b"));
        double c = std::stod(request.get_param_value("c"));
        double initial_x = std::stod(request.get_param_value("initial_x"));
        double initial_x_prime = std::stod(request.get_param_value("initial_x_prime"));
        response.set_content(equation_solver_service->solve_second_level(a, b, c, initial_x, initial_x_prime)->display(), "text/plain");
    });
};
