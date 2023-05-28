#include <iostream>
#include <string>
#include <memory>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/solution.hpp"
#include "calc/equation_solver.hpp"

int main() {
    std::cout << "Greetings at differential equations solver. I can solve linear homogenous differential equations of 2-nd order: a*x''+b*x'+c*x=0" << std::endl;
    
    input::InputParser input_parser;
    auto [a, b, c] = input_parser.receive_input();

    input::InputFormatter input_formatter;
    std::string equation = input_formatter.format_equation(a, b, c);

    std::cout << "The equation to be solved: " << equation << std::endl;

    calc::EquationSolver equation_solver;
    std::unique_ptr<calc::Solution> solution = equation_solver.find_general_solution(a, b, c);

    std::cout << "General solution is: " <<  solution->display() << std::endl;
}
