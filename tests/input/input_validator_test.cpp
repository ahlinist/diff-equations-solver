#include "../../src/input/input_validator.hpp"

#include <tuple>

#include <gtest/gtest.h>

TEST(InputValidatorTestSuite, ThrowsInvalidInputExceptionForBothXAndXPrimeEqualZero) {
    input::InputValidatorImpl input_validator{};

    try {
        input_validator.validate_second_order(1, 2, 3, 0, 0);
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Initial conditions x and x' should not be 0 simultaneously.\n", e.what());
    }
}

TEST(InputValidatorTestSuite, PassesWithInitialXNonZero) {
    input::InputValidatorImpl input_validator{};
    input_validator.validate_second_order(1, 2, 3, 4, 0);
    //nothing thrown
}

TEST(InputValidatorTestSuite, PassesWithInitialXPrimeNonZero) {
    input::InputValidatorImpl input_validator{};
    input_validator.validate_second_order(1, 2, 3, 0, 4);
    //nothing thrown
}

TEST(InputValidatorTestSuite, ThrowsInvalidInputForTwoReasons) {
    input::InputValidatorImpl input_validator{};
    
    try {
        input_validator.validate_second_order(1, 2, -3, 0, 0);
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Initial conditions x and x' should not be 0 simultaneously.\na, b and c need to be greater than 0.\n", e.what());
    }
}

class InputValidatorMultipleParametersTests :public ::testing::TestWithParam<std::tuple<double, double, double, double, double>> {
};

TEST_P(InputValidatorMultipleParametersTests, CheckIfInvalidInputExceptionIsThrown) {
    //given
    double a = std::get<0>(GetParam());
    double b = std::get<1>(GetParam());
    double c = std::get<2>(GetParam());
    double initial_x = std::get<3>(GetParam());
    double initial_x_prime = std::get<4>(GetParam());

    input::InputValidatorImpl input_validator{};

    //when
    try {
        input_validator.validate_second_order(a, b, c, initial_x, initial_x_prime);
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("a, b and c need to be greater than 0.\n", e.what());
    }
}

INSTANTIATE_TEST_CASE_P(
        CheckIfInvalidInputExceptionIsThrown,
        InputValidatorMultipleParametersTests,
        ::testing::Values(
                std::make_tuple(-1, 1, 1, 1, 1),
                std::make_tuple(1, -1, 1, 1, 1),
                std::make_tuple(1, 1, -1, 1, 1),
                std::make_tuple(-1, -1, 1, 1, 1),
                std::make_tuple(1, -1, -1, 1, 1),
                std::make_tuple(-1, 1, -1, 1, 1),
                std::make_tuple(-1, -1, -1, 1, 1)));
