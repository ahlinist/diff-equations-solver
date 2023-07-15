#include <string>

#include <gtest/gtest.h>

#include "../../src/text/equation_formatter.hpp"

class FormatUnderDampedResultMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, long double, long double, long double, long double>> {
};

TEST_P(FormatUnderDampedResultMultipleParametersTests, CheckIfResultSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    long double first_root_real = std::get<1>(GetParam());
    long double first_root_imaginary = std::get<2>(GetParam());
    long double coefficient_a = std::get<3>(GetParam());
    long double coefficient_b = std::get<4>(GetParam());

    //when
    text::SecondOrderEquationFormatter formatter{};

    //then
    ASSERT_EQ(expected, formatter.format_under_damped_result(first_root_real, first_root_imaginary, coefficient_a, coefficient_b));
}

INSTANTIATE_TEST_CASE_P(
        CheckIfResultSolutionIsPrintedCorrectly,
        FormatUnderDampedResultMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = cos(t)", 0, 1, 1, 0),
                std::make_tuple("x = e^(11t)*(9cos(7t)+13sin(7t))", 11, 7, 9, 13),
                std::make_tuple("x = e^(-2t)*-3cos(7t)", -2, 7, -3, 0),
                std::make_tuple("x = e^(-2t)*5cos(2t)", -2, 2, 5, 0),
                std::make_tuple("x = e^(2t)*5sin(2t)", 2, 2, 0, 5),
                std::make_tuple("x = e^(-t)*(-cos(t)-sin(t))", -1, 1, -1, -1),
                std::make_tuple("x = e^(t)*(cos(-t)+sin(-t))", 1, -1, 1, 1)));

class FormatOverDampedResultMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, long double, long double, long double, long double>> {
};

TEST_P(FormatOverDampedResultMultipleParametersTests, CheckIfResultSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    long double first_root_real = std::get<1>(GetParam());
    long double second_root_real = std::get<2>(GetParam());
    long double coefficient_a = std::get<3>(GetParam());
    long double coefficient_b = std::get<4>(GetParam());

    //when
    text::SecondOrderEquationFormatter formatter{};

    //then
    ASSERT_EQ(expected, formatter.format_over_damped_result(first_root_real, second_root_real, coefficient_a, coefficient_b));
}

INSTANTIATE_TEST_CASE_P(
        CheckIfResultSolutionIsPrintedCorrectly,
        FormatOverDampedResultMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = -6e^(-2t)-8e^(-3t)", -2, -3, -6, -8),
                std::make_tuple("x = 5e^(3.14t)", 2, 3.14, 0, 5),
                std::make_tuple("x = -e^(-t)-1", -1, 0, -1, -1),
                std::make_tuple("x = 3e^(t)+4e^(-t)", 1, -1, 3, 4)));

class FormarCriticallyDampedResultMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, long double, long double, long double>> {
};

TEST_P(FormarCriticallyDampedResultMultipleParametersTests, CheckIfResultSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    long double first_root_real = std::get<1>(GetParam());
    long double coefficient_a = std::get<2>(GetParam());
    long double coefficient_b = std::get<3>(GetParam());

    //when
    text::SecondOrderEquationFormatter formatter{};

    //then
    ASSERT_EQ(expected, formatter.format_critically_damped_result(first_root_real, coefficient_a, coefficient_b));
}

INSTANTIATE_TEST_CASE_P(
        CheckIfResultSolutionIsPrintedCorrectly,
        FormarCriticallyDampedResultMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = (11+15t)*e^(1.2t)", 1.2, 11, 15),
                std::make_tuple("x = (-6-8t)*e^(-2t)", -2, -6, -8),
                std::make_tuple("x = 5t", 0, 0, 5),
                std::make_tuple("x = (-1-t)*e^(-t)", -1, -1, -1),
                std::make_tuple("x = t*e^(t)", 1, 0, 1)));
