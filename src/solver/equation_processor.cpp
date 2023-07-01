#include "equation_processor.hpp"

#include <iostream>
#include <string>
#include <memory>

#include "../input/input_parser.hpp"
#include "../calc/equation_solver_selector.hpp"
#include "../calc/solution.hpp"
#include "../calc/equation_solver.hpp"
#include "../service/equation_solver_service.hpp"

EquationProcessor::EquationProcessor(
        const std::shared_ptr<input::InputParser> input_parser, 
        const std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector) 
    : input_parser{ input_parser }, equation_solver_selector{ equation_solver_selector }
    {}

void EquationProcessor::process() {
    std::cout << "Greetings at differential equations solver. I can solve linear homogenous differential equations of 2-nd order: a*x''+b*x'+c*x=0" << std::endl;
    auto [a, b, c, initial_x, initial_x_prime] = input_parser->receive_input();
    service::EquationSolverServiceImpl service{equation_solver_selector};
    std::shared_ptr<calc::Solution> solution = service.solve_second_level(a, b, c, initial_x, initial_x_prime);

    std::cout << "Solution: " << solution->display() << std::endl;
}
