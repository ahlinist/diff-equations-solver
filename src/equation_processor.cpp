#include "equation_processor.hpp"

#include <iostream>
#include <string>
#include <memory>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_selector.hpp"
#include "calc/solution.hpp"
#include "calc/equation_solver.hpp"

EquationProcessor::EquationProcessor(
        const std::shared_ptr<input::InputParser> input_parser, 
        const std::shared_ptr<input::InputFormatter> input_formatter, 
        const std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector) 
    : input_parser{ input_parser }, input_formatter{ input_formatter }, equation_solver_selector{ equation_solver_selector }
    {}

void EquationProcessor::process() {
    std::cout << "Greetings at differential equations solver. I can solve linear homogenous differential equations of 2-nd order: a*x''+b*x'+c*x=0" << std::endl;
    auto [a, b, c, initial_x, initial_x_prime] = input_parser->receive_input();

    std::string equation = input_formatter->format_equation(a, b, c);
    std::cout << "The equation to be solved: " << equation << std::endl;

    long double discriminant = b * b - 4 * a * c;
    std::shared_ptr<calc::EquationSolver> equation_solver = equation_solver_selector->select_equation_solver(discriminant);
    std::shared_ptr<calc::Solution> solution = equation_solver->solve(discriminant, a, b, c, initial_x, initial_x_prime);

    std::cout << "Solution: " << solution->display() << std::endl;
}
