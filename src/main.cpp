
#include "equation_processor.hpp"

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_factory.hpp"

int main() {
   input::InputParser input_parser{}; 
   input::InputFormatter input_formatter{}; 
   calc::EquationSolverFactory equation_solver_factory{};

   EquationProcessor equation_processor{input_parser, input_formatter, equation_solver_factory};
   equation_processor.process();
}
