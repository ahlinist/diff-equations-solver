
#include "solver/equation_processor.hpp"

#include <memory>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_selector.hpp"

int main() {
    std::shared_ptr<input::InputParser> input_parser = std::make_shared<input::ConsoleInputParser>(); 
    std::shared_ptr<input::InputFormatter> input_formatter = std::make_shared<input::SecondOrderInputFormatter>(); 

    std::shared_ptr<calc::EquationSolver> under_damped_equation_solver = std::make_shared<calc::UnderDampedEquationSolver>();
    std::shared_ptr<calc::EquationSolver> over_damped_equation_solver = std::make_shared<calc::OverDampedEquationSolver>();
    std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver = std::make_shared<calc::CriticallyDampedEquationSolver>();
    std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector = std::make_shared<calc::SecondOrderEquationSolverSelector>(
        under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver);

   EquationProcessor equation_processor{input_parser, input_formatter, equation_solver_selector};
   equation_processor.process();
}
