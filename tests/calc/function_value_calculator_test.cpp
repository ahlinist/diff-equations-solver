#include <memory>
#include <cmath>

#include <gtest/gtest.h>

#include "../../src/calc/function_value_calculator.hpp"
#include "../../src/calc/solution.hpp"

const double TOLERANCE = 0.00001;

TEST(FunctionValueCalculatorTestSuite, ShouldReturnValueOfCriticallyDampedSolutionForAGivenTime) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    std::string initial_equation = "initial equation";
    std::string result_equation = "result equation";
    long double expected = 0.947347;
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::CriticallyDampedSolution>(
        calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}, 1, 3, initial_equation, result_equation, 0.6666666666666666, 1});

    //when
    long double actual = value_calculator.calculate_value_at(solution, 2);

    //then
    EXPECT_NEAR(actual, expected, TOLERANCE);
}

TEST(FunctionValueCalculatorTestSuite, ShouldReturnValueOfUnderDampedSolutionForAGivenTime) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    std::string initial_equation = "initial equation";
    std::string result_equation = "result equation";
    long double expected = 0.276156;
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::UnderDampedSolution>(
        calc::UnderDampedSolution{{-0.5, 0.5}, {-0.5, -0.5}, 1, 0.25, initial_equation, result_equation, 5.202346306638418, 1});

    //when
    long double actual = value_calculator.calculate_value_at(solution, 2);

    //then
    EXPECT_NEAR(actual, expected, TOLERANCE);
}

TEST(FunctionValueCalculatorTestSuite, ShouldReturnValueOfOverDampedSolutionForAGivenTime) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    std::string initial_equation = "initial equation";
    std::string result_equation = "result equation";
    long double expected = 2.13401;
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::OverDampedSolution>(
        calc::OverDampedSolution{{-2, 0}, {-0.5, 0}, -4, 6, initial_equation, result_equation, 0.6538861686744841, 1});

    //when
    long double actual = value_calculator.calculate_value_at(solution, 2);

    //then
    EXPECT_NEAR(actual, expected, TOLERANCE);
}
