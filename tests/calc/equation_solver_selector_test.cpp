#include <memory>
#include <cmath>

#include <gtest/gtest.h>

#include "../../src/calc/equation_solver_selector.hpp"
#include "../../src/calc/equation_solver.hpp"

//TODO: use mocks instead of real instances of solvers
//TODO: try out setup method or so

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToCriticallyDampedEquationSolver) {
    //given
    long double discriminant = 0;
    std::shared_ptr<calc::EquationSolver> under_damped_equation_solver = std::make_shared<calc::UnderDampedEquationSolver>(calc::UnderDampedEquationSolver{});
    std::shared_ptr<calc::EquationSolver> over_damped_equation_solver = std::make_shared<calc::OverDampedEquationSolver>(calc::OverDampedEquationSolver{});
    std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver = std::make_shared<calc::CriticallyDampedEquationSolver>(calc::CriticallyDampedEquationSolver{});
    calc::SecondOrderEquationSolverSelector equation_solver_selector{under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver};
    calc::CriticallyDampedEquationSolver expected = calc::CriticallyDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector.select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToOverDampedEquationSolver) {
    //given
    long double discriminant = 1;
    std::shared_ptr<calc::EquationSolver> under_damped_equation_solver = std::make_shared<calc::UnderDampedEquationSolver>(calc::UnderDampedEquationSolver{});
    std::shared_ptr<calc::EquationSolver> over_damped_equation_solver = std::make_shared<calc::OverDampedEquationSolver>(calc::OverDampedEquationSolver{});
    std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver = std::make_shared<calc::CriticallyDampedEquationSolver>(calc::CriticallyDampedEquationSolver{});
    calc::SecondOrderEquationSolverSelector equation_solver_selector{under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver};    calc::OverDampedEquationSolver expected = calc::OverDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector.select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToUnderDampedEquationSolver) {
    //given
    long double discriminant = -1;
    std::shared_ptr<calc::EquationSolver> under_damped_equation_solver = std::make_shared<calc::UnderDampedEquationSolver>(calc::UnderDampedEquationSolver{});
    std::shared_ptr<calc::EquationSolver> over_damped_equation_solver = std::make_shared<calc::OverDampedEquationSolver>(calc::OverDampedEquationSolver{});
    std::shared_ptr<calc::EquationSolver> critically_damped_equation_solver = std::make_shared<calc::CriticallyDampedEquationSolver>(calc::CriticallyDampedEquationSolver{});
    calc::SecondOrderEquationSolverSelector equation_solver_selector{under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver};    calc::UnderDampedEquationSolver expected = calc::UnderDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector.select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}
