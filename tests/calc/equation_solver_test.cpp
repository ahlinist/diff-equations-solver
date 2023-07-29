#include <memory>
#include <cmath>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/calc/equation_solver.hpp"
#include "../../src/calc/solution.hpp"

TEST(EquationSolverTestSuite, ShouldReturnPointerToCriticallyDampedSolution) {
    //given
    calc::CriticallyDampedEquationSolver equation_solver{};
    calc::CriticallyDampedSolution expected = calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}, 1, 3};

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.solve(0, 1, 2, 1, 1, 2);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToUnderDampedGeneralSolution) {
    //given
    calc::UnderDampedEquationSolver equation_solver{};
    calc::UnderDampedSolution expected = calc::UnderDampedSolution{{-0.5, 0.5}, {-0.5, -0.5}, 1, 0.25};

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.solve(-4, 2, 2, 1, 1, 0);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToOverDampedGeneralSolution) {
    //given
    calc::OverDampedEquationSolver equation_solver{};
    calc::OverDampedSolution expected = calc::OverDampedSolution{{-2, 0}, {-0.5, 0}, -4, 6};

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.solve(9, 2, 5, 2, 2, 5);

    //then
    EXPECT_EQ(*actual, expected);
}
