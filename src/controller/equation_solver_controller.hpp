#pragma once

#include <memory>
#include <string>

#include "../service/equation_solver_service.hpp"
#include "../../libs/httplib.h"

namespace controller {
    class EquationSolverController {
    protected:
        std::shared_ptr<httplib::Server> server;
        std::shared_ptr<service::EquationSolverService> equation_solver_service;
    public:
        explicit EquationSolverController(
            const std::shared_ptr<httplib::Server> server, const std::shared_ptr<service::EquationSolverService> equation_solver_service);
        virtual ~EquationSolverController() {}
        virtual void enable() = 0;
    };

    class EquationSolverControllerImpl : public EquationSolverController {
    public:
        using EquationSolverController::EquationSolverController;
        void enable() override;
    };
}
