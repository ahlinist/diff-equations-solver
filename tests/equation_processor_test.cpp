#include <tuple>
#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/equation_processor.hpp"

namespace input {
    class MockInputParser : public input::InputParser {
    public:
        MOCK_METHOD((std::tuple<double, double, double, double, double>), receive_input, (), (override));
    };
}

TEST(EquationProcessorTestSuite, ShouldProcessEquationInputAndPrintSolution) {
    std::shared_ptr<input::MockInputParser> input_parser = std::make_shared<input::MockInputParser>(); 
    input::InputFormatter input_formatter{}; 
    calc::EquationSolverFactory equation_solver_factory{};
    EquationProcessor equation_processor{input_parser, input_formatter, equation_solver_factory};

    EXPECT_CALL(*input_parser, receive_input())
        .WillOnce(::testing::Return(std::make_tuple(6.0, 7.0, 8.0, 9.0, 10.0)));

    equation_processor.process();
}
