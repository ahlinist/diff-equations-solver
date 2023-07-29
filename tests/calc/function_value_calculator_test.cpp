#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "../../src/calc/function_value_calculator.hpp"
#include "../../src/calc/solution.hpp"
#include "../../src/model/domain_model.hpp"

const double TOLERANCE = 0.00001;

TEST(FunctionValueCalculatorTestSuite, ShouldReturnValueOfCriticallyDampedSolutionForAGivenTime) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    long double expected = 0.947347;
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}, 1, 3});

    //when
    long double actual = value_calculator.calculate_value_at_time(solution, 2);

    //then
    EXPECT_NEAR(actual, expected, TOLERANCE);
}

TEST(FunctionValueCalculatorTestSuite, ShouldReturnValueOfUnderDampedSolutionForAGivenTime) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    long double expected = 0.276156;
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{{-0.5, 0.5}, {-0.5, -0.5}, 1, 0.25});

    //when
    long double actual = value_calculator.calculate_value_at_time(solution, 2);

    //then
    EXPECT_NEAR(actual, expected, TOLERANCE);
}

TEST(FunctionValueCalculatorTestSuite, ShouldReturnValueOfOverDampedSolutionForAGivenTime) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    long double expected = 2.13401;
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::OverDampedSolution>(calc::OverDampedSolution{{-2, 0}, {-0.5, 0}, -4, 6});

    //when
    long double actual = value_calculator.calculate_value_at_time(solution, 2);

    //then
    EXPECT_NEAR(actual, expected, TOLERANCE);
}

TEST(FunctionValueCalculatorTestSuite, ShouldReturnVectorOfFunctionDataPointsForCriticallyDampedSolution) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    model::FunctionDataPoint expected0{0, 1};
    model::FunctionDataPoint expected39{0.443868, 1.49584};
    model::FunctionDataPoint expected56{0.637349, 1.53958};
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}, 1, 3});

    //when
    std::vector<model::FunctionDataPoint> actual = value_calculator.calculate_function_values(solution);

    //then
    EXPECT_EQ(actual[0], expected0);
    EXPECT_EQ(actual[39], expected39);
    EXPECT_EQ(actual[56], expected56);
}

TEST(FunctionValueCalculatorTestSuite, ShouldReturnVectorOfFunctionDataPointsForOverDampedSolution) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    model::FunctionDataPoint expected0{0, 2};
    model::FunctionDataPoint expected39{0.741088, 3.23358};
    model::FunctionDataPoint expected56{1.06413, 3.04817};
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::OverDampedSolution>(calc::OverDampedSolution{{-2, 0}, {-0.5, 0}, -4, 6});

    //when
    std::vector<model::FunctionDataPoint> actual = value_calculator.calculate_function_values(solution);

    //then
    EXPECT_EQ(actual[0], expected0);
    EXPECT_EQ(actual[39], expected39);
    EXPECT_EQ(actual[56], expected56);
}

TEST(FunctionValueCalculatorTestSuite, ShouldReturnVectorOfFunctionDataPointsForUnderDampedSolution) {
    //given
    calc::SecondOrderFunctionValueCalculator value_calculator{};
    model::FunctionDataPoint expected0{0, 1};
    model::FunctionDataPoint expected39{0.676462, 0.731782};
    model::FunctionDataPoint expected56{0.971329, 0.615943};
    std::shared_ptr<calc::Solution> solution = std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{{-0.5, 0.5}, {-0.5, -0.5}, 1, 0.25});

    //when
    std::vector<model::FunctionDataPoint> actual = value_calculator.calculate_function_values(solution);

    //then
    EXPECT_EQ(actual[0], expected0);
    EXPECT_EQ(actual[39], expected39);
    EXPECT_EQ(actual[56], expected56);
}
