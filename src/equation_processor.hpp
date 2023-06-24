#ifndef EQUATION_PROCESSOR_HEADER
#define EQUATION_PROCESSOR_HEADER

#include <memory>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_selector.hpp"

class EquationProcessor {
    std::shared_ptr<input::InputParser> input_parser;
    std::shared_ptr<input::InputFormatter> input_formatter;
    std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector;
public:
    explicit EquationProcessor(
        const std::shared_ptr<input::InputParser> input_parser, 
        const std::shared_ptr<input::InputFormatter> input_formatter, 
        const std::shared_ptr<calc::EquationSolverSelector> equation_solver_selector);
    void process();
};

#endif
