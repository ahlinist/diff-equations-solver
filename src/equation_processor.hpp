#ifndef EQUATION_PROCESSOR_HEADER
#define EQUATION_PROCESSOR_HEADER

#include <memory>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"
#include "calc/equation_solver_factory.hpp"

class EquationProcessor {
    std::shared_ptr<input::InputParser> input_parser;
    input::InputFormatter input_formatter;
    calc::EquationSolverFactory equation_solver_factory;
public:
    explicit EquationProcessor(const std::shared_ptr<input::InputParser> input_parser, const input::InputFormatter& input_formatter, const calc::EquationSolverFactory& equation_solver_factory);
    void process();
};

#endif
