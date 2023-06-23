
#include "equation_processor.hpp"

#include <memory>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_factory.hpp"

int main() {
   std::shared_ptr<input::InputParser> input_parser = std::make_shared<input::ConsoleInputParser>(); 
   std::shared_ptr<input::InputFormatter> input_formatter = std::make_shared<input::SecondOrderInputFormatter>(); 
   std::shared_ptr<calc::EquationSolverFactory> equation_solver_factory = std::make_shared<calc::SecondOrderEquationSolverFactory>();

   EquationProcessor equation_processor{input_parser, input_formatter, equation_solver_factory};
   equation_processor.process();
}
