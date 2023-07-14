#include <string>

#include <gtest/gtest.h>

#include "../../src/text/equation_formatter.hpp"

class EquationFormatterMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, double, double, double>> {
protected:
    text::SecondOrderEquationFormatter equation_formatter;
};

TEST_P(EquationFormatterMultipleParametersTests, ChecksIfTheEquationIsFormattedCorrectly) {
    std::string expected = std::get<0>(GetParam());
    double a = std::get<1>(GetParam());
    double b = std::get<2>(GetParam());
    double c = std::get<3>(GetParam());

    ASSERT_EQ(expected, equation_formatter.format_second_order(a, b ,c));
}

INSTANTIATE_TEST_CASE_P(
        FormatInitialEquation,
        EquationFormatterMultipleParametersTests,
        ::testing::Values(
                std::make_tuple("x''+x'+x=0", 1, 1, 1),
                std::make_tuple("-x''-x'-x=0", -1, -1, -1),
                std::make_tuple("-x''-x'=0", -1, -1, 0),
                std::make_tuple("-x''=0", -1, 0, 0),
                std::make_tuple("x''=0", 1, 0, 0),
                std::make_tuple("x'=0", 0, 1, 0),
                std::make_tuple("x=0", 0, 0, 1),
                std::make_tuple("3x''-2x'+x=0", 3, -2, 1),
                std::make_tuple("-x'-x=0", 0, -1, -1)));
