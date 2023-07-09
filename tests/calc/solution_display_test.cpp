#include <string>

#include <gtest/gtest.h>

#include "../../src/calc/solution.hpp"

class UnderDampedDisplayMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, double, double, double, double, double, double>> {
};

TEST_P(UnderDampedDisplayMultipleParametersTests, CheckIfParticularSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    double first_root_real = std::get<1>(GetParam());
    double first_root_imaginary = std::get<2>(GetParam());
    double second_root_real = std::get<3>(GetParam());
    double second_root_imaginary = std::get<4>(GetParam());
    double initial_x = std::get<5>(GetParam());
    double initial_x_prime = std::get<6>(GetParam());
    std::string initial_equation = "equation";

    //when
    calc::UnderDampedSolution solution{
        {first_root_real, first_root_imaginary}, {second_root_real, second_root_imaginary}, initial_x, initial_x_prime, initial_equation, 3};

    //then
    ASSERT_EQ(expected, solution.get_result_equation());
}

INSTANTIATE_TEST_CASE_P(
        DisplayParticularSolution,
        UnderDampedDisplayMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = cos(t)", 0, 1, 0, -1, 1, 0),
                std::make_tuple("x = e^(11t)*(9cos(7t)+13sin(7t))", 11, 7, 11, -7, 9, 13),
                std::make_tuple("x = e^(-2t)*-3cos(7t)", -2, 7, -2, -7, -3, 0),
                std::make_tuple("x = e^(-2t)*5cos(2t)", -2, 2, -2, -2, 5, 0),
                std::make_tuple("x = e^(2t)*5sin(2t)", 2, 2, 2, -2, 0, 5),
                std::make_tuple("x = e^(-t)*(-cos(t)-sin(t))", -1, 1, -1, -1, -1, -1),
                std::make_tuple("x = e^(t)*(cos(-t)+sin(-t))", 1, -1, 1, 1, 1, 1)));

class OverDampedDisplayMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, double, double, double, double, double, double>> {
};

TEST_P(OverDampedDisplayMultipleParametersTests, CheckIfParticularSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    double first_root_real = std::get<1>(GetParam());
    double first_root_imaginary = std::get<2>(GetParam());
    double second_root_real = std::get<3>(GetParam());
    double second_root_imaginary = std::get<4>(GetParam());
    double initial_x = std::get<5>(GetParam());
    double initial_x_prime = std::get<6>(GetParam());
    std::string initial_equation = "equation";

    //when
    calc::OverDampedSolution solution{
        {first_root_real, first_root_imaginary}, {second_root_real, second_root_imaginary}, initial_x, initial_x_prime, initial_equation, 3};

    //then
    ASSERT_EQ(expected, solution.get_result_equation());
}

INSTANTIATE_TEST_CASE_P(
        DisplayParticularSolution,
        OverDampedDisplayMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = -6e^(-2t)-8e^(-3t)", -2, 0, -3, 0, -6, -8),
                std::make_tuple("x = 5e^(3.14t)", 2, 0, 3.14, 0, 0, 5),
                std::make_tuple("x = -e^(-t)-1", -1, 0, 0, 0, -1, -1),
                std::make_tuple("x = 3e^(t)+4e^(-t)", 1, 0, -1, 0, 3, 4)));

class CriticallyDampedDisplayMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, double, double, double, double, double, double>> {
};

TEST_P(CriticallyDampedDisplayMultipleParametersTests, CheckIfParticularSolutionIsPrintedCorrectly) {
    //given
    std::string expected = std::get<0>(GetParam());
    double first_root_real = std::get<1>(GetParam());
    double first_root_imaginary = std::get<2>(GetParam());
    double second_root_real = std::get<3>(GetParam());
    double second_root_imaginary = std::get<4>(GetParam());
    double initial_x = std::get<5>(GetParam());
    double initial_x_prime = std::get<6>(GetParam());
    std::string initial_equation = "equation";

    //when
    calc::CriticallyDampedSolution solution{
        {first_root_real, first_root_imaginary}, {second_root_real, second_root_imaginary}, initial_x, initial_x_prime, initial_equation, 3};

    //then
    ASSERT_EQ(expected, solution.get_result_equation());
}

INSTANTIATE_TEST_CASE_P(
        DisplayParticularSolution,
        CriticallyDampedDisplayMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = (11+15t)*e^(1.2t)", 1.2, 0, 1.2, 0, 11, 15),
                std::make_tuple("x = (-6-8t)*e^(-2t)", -2, 0, -2, 0, -6, -8),
                std::make_tuple("x = 5t", 0, 0, 0, 0, 0, 5),
                std::make_tuple("x = (-1-t)*e^(-t)", -1, 0, -1, 0, -1, -1),
                std::make_tuple("x = t*e^(t)", 1, 0, 1, 0, 0, 1)));
