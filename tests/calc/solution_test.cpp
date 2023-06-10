#include <string>

#include <gtest/gtest.h>

#include "../../src/calc/solution.hpp"

TEST(SolutionTestSuite, DisplaysGeneralUnderDampedSolution) {
    //given
    calc::UnderDampedSolution solution{{-1.1, 2.2}, {-1.1, -2.2}};
    std::string expected = "x = e^(-1.1*t)*(A*cos(2.2*t)+B*sin(2.2*t))";

    //when
    std::string actual = solution.display_general();

    //then
    EXPECT_EQ(actual, expected);
}

TEST(SolutionTestSuite, UnderDampedThrowsInvalidArgumentWhenRealPartsDiffer) {
    try {
        calc::UnderDampedSolution solution{{-1.1, 2.2}, {-2.2, -2.2}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts of roots are different!\n", e.what());
    }
}

TEST(SolutionTestSuite, UnderDampedThrowsInvalidArgumentWhenImaginaryPartsArentOpposite) {
    try {
        calc::UnderDampedSolution solution{{-1.1, 2.2}, {-1.1, -4.2}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Values of roots imaginary parts are not opposite!\n", e.what());
    }
}

TEST(SolutionTestSuite, UnderDampedThrowsInvalidArgumentWhenRealPartsDifferAndImaginaryPartsArentOpposite) {
    try {
        calc::UnderDampedSolution solution{{-1.1, 2.2}, {-2.2, -4.2}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts of roots are different!\nValues of roots imaginary parts are not opposite!\n", e.what());
    }
}

TEST(SolutionTestSuite, DisplaysGeneralOverDampedSolution) {
    //given
    calc::OverDampedSolution solution{{-1.1, 0}, {-5.1, 0}};
    std::string expected = "x = A*e^(-1.1*t) + B*e^(-5.1*t)";

    //when
    std::string actual = solution.display_general();

    //then
    EXPECT_EQ(actual, expected);
}

TEST(SolutionTestSuite, OverDampedThrowsInvalidArgumentWhenImaginaryPartsPresent) {
    try {
        calc::OverDampedSolution solution{{-1.1, 2.2}, {-2.2, -2.2}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\n", e.what());
    }
}

TEST(SolutionTestSuite, OverDampedThrowsInvalidArgumentWhenRealPartsAreTheSame) {
    try {
        calc::OverDampedSolution solution{{-1.1, 0}, {-1.1, 0}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts are the same!\n", e.what());
    }
}

TEST(SolutionTestSuite, OverDampedThrowsInvalidArgumentWhenImaginaryPartsPresentAndRealPartsAreTheSame) {
    try {
        calc::OverDampedSolution solution{{-1.1, 2.2}, {-1.1, -4.2}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\nReal parts are the same!\n", e.what());
    }
}

TEST(SolutionTestSuite, DisplaysGeneralCriticallyDampedSolution) {
    //given
    calc::CriticallyDampedSolution solution{{-1.1, 0}, {-1.1, 0}};
    std::string expected = "x = (A + B*t)e^(-1.1*t)";

    //when
    std::string actual = solution.display_general();

    //then
    EXPECT_EQ(actual, expected);
}

TEST(SolutionTestSuite, CriticallyDampedThrowsInvalidArgumentWhenImaginaryPartsPresent) {
    try {
        calc::CriticallyDampedSolution solution{{-1.1, 2.2}, {-1.1, -2.2}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\n", e.what());
    }
}

TEST(SolutionTestSuite, CriticallyDampedThrowsInvalidArgumentWhenRealPartsAreNotTheSame) {
    try {
        calc::CriticallyDampedSolution solution{{-1.1, 0}, {-1.2, 0}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Real parts are not the same!\n", e.what());
    }
}

TEST(SolutionTestSuite, CriticallyDampedThrowsInvalidArgumentWhenImaginaryPartsPresentAndRealPartsAreNotTheSame) {
    try {
        calc::CriticallyDampedSolution solution{{-1.1, 2.2}, {-1.2, -4.2}};
        FAIL();
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Roots contain imaginary parts!\nReal parts are not the same!\n", e.what());
    }
}


TODO: test display particular here!!!