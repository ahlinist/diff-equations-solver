#include "equation_processor.hpp"

#include <iostream>
#include <string>
#include <memory>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_factory.hpp"
#include "calc/solution.hpp"
#include "calc/equation_solver.hpp"

EquationProcessor::EquationProcessor(const input::InputParser& input_parser, const input::InputFormatter& input_formatter, const calc::EquationSolverFactory& equation_solver_factory) 
    : input_parser{ input_parser }, input_formatter{ input_formatter }, equation_solver_factory{ equation_solver_factory }
    {}

void EquationProcessor::process() {
    std::cout << "Greetings at differential equations solver. I can solve linear homogenous differential equations of 2-nd order: a*x''+b*x'+c*x=0" << std::endl;
    auto [a, b, c, initial_x, initial_x_prime] = input_parser.receive_input();

    std::string equation = input_formatter.format_equation(a, b, c);
    std::cout << "The equation to be solved: " << equation << std::endl;

    long double discriminant = b * b - 4 * a * c;
    std::unique_ptr<calc::EquationSolver> equation_solver = equation_solver_factory.create_equation_solver(discriminant);
    std::shared_ptr<calc::Solution> solution = equation_solver->solve(discriminant, a, b, c, initial_x, initial_x_prime);

    std::cout << "General solution is: " <<  solution->display_general() << std::endl;
    std::cout << "Particular solution for the given initial conditions is: " << solution->display_particular() << std::endl;
}
