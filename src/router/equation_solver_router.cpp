#include "equation_solver_router.hpp"

#include <memory>

#include "../../libs/httplib.h"

#include "../controller/equation_solver_controller.hpp"

router::EquationSolverRouter::EquationSolverRouter(
        std::shared_ptr<httplib::Server> server, std::shared_ptr<controller::EquationSolverController> equation_solver_controller) 
    : server{ server }, equation_solver_controller{ equation_solver_controller } {}

void router::EquationSolverRouter::register_routes() {
    server->Get("/solution", [this](const httplib::Request& request, httplib::Response& response) {
        double a = std::stod(request.get_param_value("a"));
        double b = std::stod(request.get_param_value("b"));
        double c = std::stod(request.get_param_value("c"));
        double initial_x = std::stod(request.get_param_value("initial_x"));
        double initial_x_prime = std::stod(request.get_param_value("initial_x_prime"));
        response.set_content(equation_solver_controller->solve_second_order(a, b, c, initial_x, initial_x_prime), "text/plain");
    });
}
