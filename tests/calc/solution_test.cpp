#include <string>

#include <gtest/gtest.h>

#include "../../src/calc/solution.hpp"

TEST(SolutionTestSuite, UnderDampedThrowsInvalidArgumentWhenRealPartsDiffer) {
    try {
        calc::UnderDampedSolution solution{{-1.1, 2.2}, {-2.2, -2.2}, 1, 0, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts of roots are different!\n", e.what());
    }
}

TEST(SolutionTestSuite, UnderDampedThrowsInvalidArgumentWhenImaginaryPartsArentOpposite) {
    try {
        calc::UnderDampedSolution solution{{-1.1, 2.2}, {-1.1, -4.2}, 1, 0, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Values of roots imaginary parts are not opposite!\n", e.what());
    }
}

TEST(SolutionTestSuite, UnderDampedThrowsInvalidArgumentWhenRealPartsDifferAndImaginaryPartsArentOpposite) {
    try {
        calc::UnderDampedSolution solution{{-1.1, 2.2}, {-2.2, -4.2}, 1, 0, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts of roots are different!\nValues of roots imaginary parts are not opposite!\n", e.what());
    }
}

TEST(SolutionTestSuite, OverDampedThrowsInvalidArgumentWhenImaginaryPartsPresent) {
    try {
        calc::OverDampedSolution solution{{-1.1, 2.2}, {-2.2, -2.2}, 1, 0, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\n", e.what());
    }
}

TEST(SolutionTestSuite, OverDampedThrowsInvalidArgumentWhenRealPartsAreTheSame) {
    try {
        calc::OverDampedSolution solution{{-1.1, 0}, {-1.1, 0}, 1, 1, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts are the same!\n", e.what());
    }
}

TEST(SolutionTestSuite, OverDampedThrowsInvalidArgumentWhenImaginaryPartsPresentAndRealPartsAreTheSame) {
    try {
        calc::OverDampedSolution solution{{-1.1, 2.2}, {-1.1, -4.2}, 1, 1, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\nReal parts are the same!\n", e.what());
    }
}

TEST(SolutionTestSuite, CriticallyDampedThrowsInvalidArgumentWhenImaginaryPartsPresent) {
    try {
        calc::CriticallyDampedSolution solution{{-1.1, 2.2}, {-1.1, -2.2}, 1, 1, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\n", e.what());
    }
}

TEST(SolutionTestSuite, CriticallyDampedThrowsInvalidArgumentWhenRealPartsAreNotTheSame) {
    try {
        calc::CriticallyDampedSolution solution{{-1.1, 0}, {-1.2, 0}, 1, 1, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts are not the same!\n", e.what());
    }
}

TEST(SolutionTestSuite, CriticallyDampedThrowsInvalidArgumentWhenImaginaryPartsPresentAndRealPartsAreNotTheSame) {
    try {
        calc::CriticallyDampedSolution solution{{-1.1, 2.2}, {-1.2, -4.2}, 1, 1, "equation", 1};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\nReal parts are not the same!\n", e.what());
    }
}
