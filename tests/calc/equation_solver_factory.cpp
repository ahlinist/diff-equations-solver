#include <memory>
#include <cmath>

#include <gtest/gtest.h>

#include "../../src/calc/equation_solver_factory.hpp"
#include "../../src/calc/equation_solver.hpp"

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToCriticallyDampedEquationSolver) {
    //given
    long double discriminant = 0;
    calc::SecondOrderEquationSolverFactory equation_solver_factory{};
    calc::CriticallyDampedEquationSolver expected = calc::CriticallyDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_factory.create_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToOverDampedEquationSolver) {
    //given
    long double discriminant = 1;
    calc::SecondOrderEquationSolverFactory equation_solver_factory{};
    calc::OverDampedEquationSolver expected = calc::OverDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_factory.create_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToUnderDampedEquationSolver) {
    //given
    long double discriminant = -1;
    calc::SecondOrderEquationSolverFactory equation_solver_factory{};
    calc::UnderDampedEquationSolver expected = calc::UnderDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_factory.create_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}
