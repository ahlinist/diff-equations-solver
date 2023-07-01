#include <memory>

#include "../libs/httplib.h"

#include "solver/equation_processor.hpp"
#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_selector.hpp"

int main() {
    std::shared_ptr<input::InputParser> input_parser = std::make_shared<input::ConsoleInputParser>(); 
    std::shared_ptr<input::InputFormatter> input_formatter = std::make_shared<input::SecondOrderInputFormatter>(); 

    std::shared_ptr<calc::EquationSolver> under_damped_equation_solver = std::make_shared<calc::UnderDampedEquationSolver>(input_formatter);
    std::shared_ptr<calc::EquationSolver> over_damped_equation_solver = std::make_shared<calc::OverDampedEquationSolver>(input_formatter);
    std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver = std::make_shared<calc::CriticallyDampedEquationSolver>(input_formatter);
    std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector = std::make_shared<calc::SecondOrderEquationSolverSelector>(
        under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver);

    EquationProcessor equation_processor{input_parser, equation_solver_selector};
    equation_processor.process();
}
