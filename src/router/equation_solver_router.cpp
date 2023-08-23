#include "equation_solver_router.hpp"

#include <memory>
#include <string>

#include "../../libs/httplib.h"

#include "../controller/equation_solver_controller.hpp"

router::EquationSolverRouter::EquationSolverRouter(
        std::shared_ptr<httplib::Server> server, std::shared_ptr<controller::EquationSolverController> equation_solver_controller) 
    : server{ server }, equation_solver_controller{ equation_solver_controller } {}

void router::EquationSolverRouter::register_routes() {
    server->set_mount_point("/", "./static");

    server->Get("/", [=](const httplib::Request& request, httplib::Response& response) {
        response.set_redirect("/index.html");
    });

    server->Get("/second-order/solution", [this](const httplib::Request& request, httplib::Response& response) {
        double a = std::stod(request.get_param_value("a"));
        double b = std::stod(request.get_param_value("b"));
        double c = std::stod(request.get_param_value("c"));
        double initial_y = std::stod(request.get_param_value("initial-y"));
        double initial_y_prime = std::stod(request.get_param_value("initial-y-prime"));

        std::string responseBody{};

        try {
            response.set_content(equation_solver_controller->solve_second_order(a, b, c, initial_y, initial_y_prime), "application/json");
        } 
        catch (const std::invalid_argument& e) {
            response.status = 400;
            response.set_content(e.what(), "text/plain");
        }
    });
}
