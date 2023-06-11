#include <string>

#include <gtest/gtest.h>

#include "../../src/calc/solution.hpp"

class UnderDampedDisplayParticularMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, double, double, double, double, double, double>> {
};

TEST_P(UnderDampedDisplayParticularMultipleParametersTests, CheckIfParticularSolutionIsPrintedCorrectly) {
    std::string expected = std::get<0>(GetParam());
    double first_root_real = std::get<1>(GetParam());
    double first_root_imaginary = std::get<2>(GetParam());
    double second_root_real = std::get<3>(GetParam());
    double second_root_imaginary = std::get<4>(GetParam());
    double initial_x = std::get<5>(GetParam());
    double initial_x_prime = std::get<6>(GetParam());


    calc::UnderDampedSolution solution{{first_root_real, first_root_imaginary}, {second_root_real, second_root_imaginary}};
    solution.set_coefficient_a(initial_x);
    solution.set_coefficient_b(initial_x_prime);

    ASSERT_EQ(expected, solution.display_particular());
}

INSTANTIATE_TEST_CASE_P(
        DisplayParticularSolution,
        UnderDampedDisplayParticularMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = cos(t)", 0, 1, 0, -1, 1, 0),
                std::make_tuple("x = e^(11t)*(9cos(7t)+13sin(7t))", 11, 7, 11, -7, 9, 13),
                std::make_tuple("x = e^(-2t)*-3cos(7t)", -2, 7, -2, -7, -3, 0),
                std::make_tuple("x = e^(-2t)*5cos(2t)", -2, 2, -2, -2, 5, 0),
                std::make_tuple("x = e^(2t)*5sin(2t)", 2, 2, 2, -2, 0, 5),
                std::make_tuple("x = e^(-t)*(-cos(t)-sin(t))", -1, 1, -1, -1, -1, -1),
                std::make_tuple("x = e^(t)*(cos(-t)+sin(-t))", 1, -1, 1, 1, 1, 1)));

class OverDampedDisplayParticularMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, double, double, double, double, double, double>> {
};

TEST_P(OverDampedDisplayParticularMultipleParametersTests, CheckIfParticularSolutionIsPrintedCorrectly) {
    std::string expected = std::get<0>(GetParam());
    double first_root_real = std::get<1>(GetParam());
    double first_root_imaginary = std::get<2>(GetParam());
    double second_root_real = std::get<3>(GetParam());
    double second_root_imaginary = std::get<4>(GetParam());
    double initial_x = std::get<5>(GetParam());
    double initial_x_prime = std::get<6>(GetParam());


    calc::OverDampedSolution solution{{first_root_real, first_root_imaginary}, {second_root_real, second_root_imaginary}};
    solution.set_coefficient_a(initial_x);
    solution.set_coefficient_b(initial_x_prime);

    ASSERT_EQ(expected, solution.display_particular());
}

INSTANTIATE_TEST_CASE_P(
        DisplayParticularSolution,
        OverDampedDisplayParticularMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x = -6e^(-2t)-8e^(-3t)", -2, 0, -3, 0, -6, -8),
                std::make_tuple("x = 5e^(3.14t)", 2, 0, 3.14, 0, 0, 5),
                std::make_tuple("x = -e^(-t)-1", -1, 0, 0, 0, -1, -1),
                std::make_tuple("x = 3e^(t)+4e^(-t)", 1, 0, -1, 0, 3, 4)));
