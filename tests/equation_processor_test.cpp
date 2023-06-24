#include <tuple>
#include <memory>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/equation_processor.hpp"
#include "../src/input/input_parser.hpp"
#include "../src/input/input_formatter.hpp"
#include "../src/calc/equation_solver_selector.hpp"

//TODO: verify display methods called


class MockInputParser : public input::InputParser {
public:
    MOCK_METHOD((std::tuple<double, double, double, double, double>), receive_input, (), (override));
};

class MockInputFormatter : public input::InputFormatter {
public:
    MOCK_METHOD(std::string, format_equation, (double, double, double), (override));
};

class MockEquationSolver : public calc::EquationSolver {
public:
    MOCK_METHOD(std::shared_ptr<calc::Solution>, solve, (const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime), (override));
};

class MockEquationSolverSelector : public calc::EquationSolverSelector {
public:
    MockEquationSolverSelector() {}
    MOCK_METHOD(std::shared_ptr<calc::EquationSolver>, select_equation_solver, (const long double&), (override));
};


TEST(EquationProcessorTestSuite, ShouldProcessEquationInputAndPrintSolution) {
    std::shared_ptr<MockInputParser> input_parser = std::make_shared<MockInputParser>(); 
    std::shared_ptr<MockInputFormatter> input_formatter = std::make_shared<MockInputFormatter>(); 
    std::shared_ptr<MockEquationSolverSelector> equation_solver_selector = std::make_shared<MockEquationSolverSelector>();
    std::shared_ptr<MockEquationSolver> equation_solver = std::make_shared<MockEquationSolver>();
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{{-1.1, 2.2}, {-1.1, -2.2}, 1, 1});

    EquationProcessor equation_processor{input_parser, input_formatter, equation_solver_selector};

    EXPECT_CALL(*input_parser, receive_input())
        .WillOnce(::testing::Return(std::make_tuple(6.0, 7.0, 8.0, 9.0, 10.0)));
    EXPECT_CALL(*input_formatter, format_equation(6.0, 7.0, 8.0))
        .WillOnce(::testing::Return("6x''+7x'+8x=0"));
    EXPECT_CALL(*equation_solver_selector, select_equation_solver(-143.0))
        .WillOnce(::testing::Return(equation_solver));
    EXPECT_CALL(*equation_solver, solve(-143, 6.0, 7.0, 8.0, 9.0, 10.0))
        .WillOnce(::testing::Return(solution));

    equation_processor.process();
}
