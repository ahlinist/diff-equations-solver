#include <memory>
#include <cmath>

#include <gtest/gtest.h>

#include "../../src/calc/equation_solver.hpp"
#include "../../src/calc/solution.hpp"

TEST(EquationSolverTestSuite, ShouldReturnPointerToCriticallyDampedSolution) {
    //given
    calc::CriticallyDampedEquationSolver equation_solver{};
    calc::CriticallyDampedSolution expected = calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}};

    //when
    std::unique_ptr<calc::Solution> actual = equation_solver.find_general_solution(0, 1, 2, 1);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToUnderDampedSolution) {
    //given
    calc::UnderDampedEquationSolver equation_solver{};
    long double imaginary_part = std::sqrt(static_cast<long double>(3)) / 2;
    calc::UnderDampedSolution expected = calc::UnderDampedSolution{{-0.5, imaginary_part}, {-0.5, -imaginary_part}};

    //when
    std::unique_ptr<calc::Solution> actual = equation_solver.find_general_solution(-3, 1, 1, 1);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToOverDampedSolution) {
    //given
    calc::OverDampedEquationSolver equation_solver{};
    calc::OverDampedSolution expected = calc::OverDampedSolution{{-2, 0}, {-0.5, 0}};

    //when
    std::unique_ptr<calc::Solution> actual = equation_solver.find_general_solution(9, 2, 5, 2);

    //then
    EXPECT_EQ(*actual, expected);
}
