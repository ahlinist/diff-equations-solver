#include <memory>
#include <cmath>

#include <gtest/gtest.h>

#include "../../src/calc/equation_solver.hpp"
#include "../../src/calc/solution.hpp"

TEST(EquationSolverTestSuite, ShouldReturnPointerToCriticallyDampedGeneralSolution) {
    //given
    calc::CriticallyDampedEquationSolver equation_solver{};
    calc::CriticallyDampedSolution expected = calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}};

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.find_general_solution(0, 1, 2, 1);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToUnderDampedGeneralSolution) {
    //given
    calc::UnderDampedEquationSolver equation_solver{};
    long double imaginary_part = std::sqrt(static_cast<long double>(3)) / 2;
    calc::UnderDampedSolution expected = calc::UnderDampedSolution{{-0.5, imaginary_part}, {-0.5, -imaginary_part}};

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.find_general_solution(-3, 1, 1, 1);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToOverDampedGeneralSolution) {
    //given
    calc::OverDampedEquationSolver equation_solver{};
    calc::OverDampedSolution expected = calc::OverDampedSolution{{-2, 0}, {-0.5, 0}};

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.find_general_solution(9, 2, 5, 2);

    //then
    EXPECT_EQ(*actual, expected);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToCriticallyDampedParticularSolution) {
    //given
    calc::CriticallyDampedEquationSolver equation_solver{};
    std::shared_ptr<calc::CriticallyDampedSolution> solution = std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}});
    
    EXPECT_EQ(solution->get_coefficient_a(), 0);
    EXPECT_EQ(solution->get_coefficient_b(), 0);

    //when
    equation_solver.find_particular_solution(solution, 1, 2);

    //then
    EXPECT_EQ(solution->get_coefficient_a(), 1);
    EXPECT_EQ(solution->get_coefficient_b(), 3);
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToUnderDampedParticularSolution) {
    //given
    calc::UnderDampedEquationSolver equation_solver{};
    long double imaginary_part = std::sqrt(static_cast<long double>(3)) / 2;
    std::shared_ptr<calc::UnderDampedSolution> solution = std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{{-0.5, imaginary_part}, {-0.5, -imaginary_part}});

    EXPECT_EQ(solution->get_coefficient_a(), 0);
    EXPECT_EQ(solution->get_coefficient_b(), 0);

    //when
    equation_solver.find_particular_solution(solution, 1, 1);

    //then
    EXPECT_EQ(solution->get_coefficient_a(), 1);
    EXPECT_EQ(solution->get_coefficient_b(), std::sqrt(3));
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToOverDampedParticularSolution) {
    //given
    calc::OverDampedEquationSolver equation_solver{};
    std::shared_ptr<calc::OverDampedSolution> solution = std::make_shared<calc::OverDampedSolution>(calc::OverDampedSolution{{-2, 0}, {-0.5, 0}});

    EXPECT_EQ(solution->get_coefficient_a(), 0);
    EXPECT_EQ(solution->get_coefficient_b(), 0);

    //when
    equation_solver.find_particular_solution(solution, 2, 5);

    //then
    EXPECT_EQ(solution->get_coefficient_a(), -4);
    EXPECT_EQ(solution->get_coefficient_b(), 6);
}
