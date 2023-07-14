#include <memory>
#include <cmath>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/text/equation_formatter.hpp"
#include "../../src/calc/equation_solver.hpp"
#include "../../src/calc/solution.hpp"

class MockEquationFormatter : public text::EquationFormatter {
public:
    MOCK_METHOD(std::string, format_second_order, (const double&, const double&, const double&), (override));
};

TEST(EquationSolverTestSuite, ShouldReturnPointerToCriticallyDampedSolution) {
    //given
    std::shared_ptr<MockEquationFormatter> equation_formatter = std::make_shared<MockEquationFormatter>(); 
    calc::CriticallyDampedEquationSolver equation_solver{equation_formatter};
    std::string initial_equation = "initial equation";
    calc::CriticallyDampedSolution expected = calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}, 1, 3, initial_equation, 0.6666666666666666};

    EXPECT_CALL(*equation_formatter, format_second_order(1, 2, 1))
        .WillOnce(::testing::Return(initial_equation));

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.solve(0, 1, 2, 1, 1, 2);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToUnderDampedGeneralSolution) {
    //given
    std::shared_ptr<MockEquationFormatter> equation_formatter = std::make_shared<MockEquationFormatter>(); 
    calc::UnderDampedEquationSolver equation_solver{equation_formatter};
    std::string initial_equation = "initial equation";
    calc::UnderDampedSolution expected = calc::UnderDampedSolution{{-0.5, 0.5}, {-0.5, -0.5}, 1, 0.25, initial_equation, 5.202346306638418};

    EXPECT_CALL(*equation_formatter, format_second_order(2, 2, 1))
        .WillOnce(::testing::Return(initial_equation));

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.solve(-4, 2, 2, 1, 1, 0);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToOverDampedGeneralSolution) {
    //given
    std::shared_ptr<MockEquationFormatter> equation_formatter = std::make_shared<MockEquationFormatter>(); 
    calc::OverDampedEquationSolver equation_solver{equation_formatter};
    std::string initial_equation = "initial equation";
    calc::OverDampedSolution expected = calc::OverDampedSolution{{-2, 0}, {-0.5, 0}, -4, 6, initial_equation, 0.6538861686744841};

    EXPECT_CALL(*equation_formatter, format_second_order(2, 5, 2))
        .WillOnce(::testing::Return(initial_equation));

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.solve(9, 2, 5, 2, 2, 5);

    //then
    EXPECT_EQ(*actual, expected);
}
