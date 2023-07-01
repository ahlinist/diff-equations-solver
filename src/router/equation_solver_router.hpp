#pragma once

#include <memory>

#include "../../libs/httplib.h"

#include "../controller/equation_solver_controller.hpp"

namespace router {
    class EquationSolverRouter {
        std::shared_ptr<httplib::Server> server;
        std::shared_ptr<controller::EquationSolverController> equation_solver_controller;
    public:
        void register_routes();
        explicit EquationSolverRouter(
            std::shared_ptr<httplib::Server> server, std::shared_ptr<controller::EquationSolverController> equation_solver_controller);
    };
}
