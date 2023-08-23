#include <string>

#include <gtest/gtest.h>

#include "../../src/text/equation_formatter.hpp"
#include "../../src/calc/solution.hpp"

class FormatUnderDampedResultMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, calc::UnderDampedSolution>> {
};

TEST_P(FormatUnderDampedResultMultipleParametersTests, CheckIfResultSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    calc::UnderDampedSolution solution = std::get<1>(GetParam());
    text::SecondOrderEquationFormatter formatter{};

    //when
    std::string actual = formatter.format_second_order_solution(std::make_shared<calc::UnderDampedSolution>(solution));
    //then
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P(
        CheckIfResultSolutionIsPrintedCorrectly,
        FormatUnderDampedResultMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("y = cos(t)", calc::UnderDampedSolution{{0, 1}, {0, -1}, 1, 0}),
                std::make_tuple("y = e^(11t)*(9cos(7t)+13sin(7t))", calc::UnderDampedSolution{{11, 7}, {11, -7}, 9, 13}),
                std::make_tuple("y = e^(-2t)*-3cos(7t)", calc::UnderDampedSolution{{-2, 7}, {-2, -7}, -3, 0}),
                std::make_tuple("y = e^(-2t)*5cos(2t)", calc::UnderDampedSolution{{-2, 2}, {-2, -2}, 5, 0}),
                std::make_tuple("y = e^(2t)*5sin(2t)", calc::UnderDampedSolution{{2, 2}, {2, -2}, 0, 5}),
                std::make_tuple("y = e^(-t)*(-cos(t)-sin(t))", calc::UnderDampedSolution{{-1, 1}, {-1, -1}, -1, -1}),
                std::make_tuple("y = e^(t)*(cos(-t)+sin(-t))", calc::UnderDampedSolution{{1, -1}, {1, 1}, 1, 1})));

class FormatOverDampedResultMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, calc::OverDampedSolution>> {
};

TEST_P(FormatOverDampedResultMultipleParametersTests, CheckIfResultSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    calc::OverDampedSolution solution = std::get<1>(GetParam());
    text::SecondOrderEquationFormatter formatter{};

    //when
    std::string actual = formatter.format_second_order_solution(std::make_shared<calc::OverDampedSolution>(solution));
    //then
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P(
        CheckIfResultSolutionIsPrintedCorrectly,
        FormatOverDampedResultMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("y = -6e^(-2t)-8e^(-3t)", calc::OverDampedSolution{{-2, 0}, {-3, 0}, -6, -8}),
                std::make_tuple("y = 5e^(3.14t)", calc::OverDampedSolution{{2, 0}, {3.14, 0}, 0, 5}),
                std::make_tuple("y = -e^(-t)-1", calc::OverDampedSolution{{-1, 0}, {0, 0}, -1, -1}),
                std::make_tuple("y = 3e^(t)+4e^(-t)", calc::OverDampedSolution{{1, 0}, {-1, 0}, 3, 4})));

class FormarCriticallyDampedResultMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, calc::CriticallyDampedSolution>> {
};

TEST_P(FormarCriticallyDampedResultMultipleParametersTests, CheckIfResultSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    calc::CriticallyDampedSolution solution = std::get<1>(GetParam());
    text::SecondOrderEquationFormatter formatter{};

    //when
    std::string actual = formatter.format_second_order_solution(std::make_shared<calc::CriticallyDampedSolution>(solution));

    //then
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P(
        CheckIfResultSolutionIsPrintedCorrectly,
        FormarCriticallyDampedResultMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("y = (11+15t)*e^(1.2t)", calc::CriticallyDampedSolution{{1.2, 0}, {1.2, 0}, 11, 15}),
                std::make_tuple("y = (-6-8t)*e^(-2t)", calc::CriticallyDampedSolution{{-2, 0}, {-2, 0}, -6, -8}),
                std::make_tuple("y = 5t", calc::CriticallyDampedSolution{{0, 0}, {0, 0}, 0, 5}),
                std::make_tuple("y = (-1-t)*e^(-t)", calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}, -1, -1}),
                std::make_tuple("y = t*e^(t)", calc::CriticallyDampedSolution{{1, 0}, {1, 0}, 0, 1})));
