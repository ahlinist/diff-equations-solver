#include "../../src/input/input_validator.hpp"

#include <gtest/gtest.h>

TEST(InputValidatorTestSuite, ThrowsInvalidInputExceptionForBothXAndXPrimeEqualZero) {
    input::InputValidatorImpl input_validator{};

    try {
        input_validator.validate_second_order(1, 2, 3, 0, 0);
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Initial conditions x and x' should not be 0 simultaneously.", e.what());
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
