#pragma once

#include <memory>
#include <string>

#include "../service/equation_solver_service.hpp"
#include "../mapper/solution_mapper.hpp"
#include "../input/input_validator.hpp"

namespace controller {
    class EquationSolverController {
    protected:
        std::shared_ptr<service::EquationSolverService> equation_solver_service;
        std::shared_ptr<mapper::SolutionMapper> solution_mapper;
        std::shared_ptr<input::InputValidator> input_validator;
    public:
        explicit EquationSolverController(
            const std::shared_ptr<service::EquationSolverService> equation_solver_service, 
            const std::shared_ptr<mapper::SolutionMapper> solution_mapper,
            const std::shared_ptr<input::InputValidator> input_validator);
        virtual ~EquationSolverController() {}
        virtual std::string solve_second_order(
            const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) = 0;
    };

    class EquationSolverControllerImpl : public EquationSolverController {
    public:
        using EquationSolverController::EquationSolverController;
        std::string solve_second_order(
            const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };
}
