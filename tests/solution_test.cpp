#include <gtest/gtest.h>
#include <string>

#include "../src/calc/solution.hpp"

TEST(SolutionTestSuite, DisplaysGeneralUnderDampedSolution) {
    //given
    calc::UnderDampedSolution solution{{-1.1, 2.2}, {-1.1, -2.2}};
    std::string expected = "x = e^(-1.1*t)*(A*cos(2.2*t)+i*B*sin(2.2*t))";

    //when
    std::string actual = solution.display_general();

    EXPECT_EQ(actual, expected);
}

TEST(SolutionTestSuite, DisplaysGeneralOverDampedSolution) {
    //given
    calc::OverDampedSolution solution{{-1.1, 0}, {-5.1, 0}};
    std::string expected = "x = A*e^(-1.1*t) + B*e^(-5.1*t)";

    //when
    std::string actual = solution.display_general();

    EXPECT_EQ(actual, expected);
}

TEST(SolutionTestSuite, DisplaysGeneralCriticallyDampedSolution) {
    //given
    calc::CriticallyDampedSolution solution{{-1.1, 0}, {-1.1, 0}};
    std::string expected = "x = (A + B*t)e^(-1.1*t)";

    //when
    std::string actual = solution.display_general();

    EXPECT_EQ(actual, expected);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
