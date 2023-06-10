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
    std::shared_ptr<calc::CriticallyDampedSolution> general_solution = std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{{-1, 0}, {-1, 0}});

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.find_particular_solution(general_solution, 1, 2);

    //then
    EXPECT_EQ(actual->display_particular(), "x = (1 + 3*t)e^(-1*t)");
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToUnderDampedParticularSolution) {
    //given
    calc::UnderDampedEquationSolver equation_solver{};
    long double imaginary_part = std::sqrt(static_cast<long double>(3)) / 2;
    std::shared_ptr<calc::UnderDampedSolution> general_solution = std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{{-0.5, imaginary_part}, {-0.5, -imaginary_part}});

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.find_particular_solution(general_solution, 1, 1);

    //then
    EXPECT_EQ(actual->display_particular(), "x = e^(-0.5*t)*(1*cos(0.866025*t)+1.73205*sin(0.866025*t))");
}

TEST(EquationSolverTestSuite, ShouldReturnPointerToOverDampedParticularSolution) {
    //given
    calc::OverDampedEquationSolver equation_solver{};
    std::shared_ptr<calc::OverDampedSolution> general_solution = std::make_shared<calc::OverDampedSolution>(calc::OverDampedSolution{{-2, 0}, {-0.5, 0}});

    //when
    std::shared_ptr<calc::Solution> actual = equation_solver.find_particular_solution(general_solution, 2, 5);

    //then
    EXPECT_EQ(actual->display_particular(), "x = -4*e^(-2*t) + 6*e^(-0.5*t)");
}

TODO: test not display solution, but getters for coefficients! create the required getters!