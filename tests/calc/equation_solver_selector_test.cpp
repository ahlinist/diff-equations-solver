#include <memory>
#include <cmath>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/calc/equation_solver_selector.hpp"
#include "../../src/calc/equation_solver.hpp"

//TODO: try out setup method or so

class MockUnderDampedEquationSolver : public calc::EquationSolver {
public:
    std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
        return nullptr;
    }
};

class MockOverDampedEquationSolver : public calc::EquationSolver {
public:
    std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
        return nullptr;
    }

};

class MockCriticallyDampedEquationSolver : public calc::EquationSolver {
public:
    std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
        return nullptr;
    }
};

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToCriticallyDampedEquationSolver) {
    //given
    long double discriminant = 0;
    std::shared_ptr<MockUnderDampedEquationSolver> under_damped_equation_solver = std::make_shared<MockUnderDampedEquationSolver>();
    std::shared_ptr<MockOverDampedEquationSolver> over_damped_equation_solver = std::make_shared<MockOverDampedEquationSolver>();
    std::shared_ptr<MockCriticallyDampedEquationSolver> critically_damped_equation_solver = std::make_shared<MockCriticallyDampedEquationSolver>();
    calc::SecondOrderEquationSolverSelector equation_solver_selector{under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver};
    MockCriticallyDampedEquationSolver expected = MockCriticallyDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector.select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToOverDampedEquationSolver) {
    //given
    long double discriminant = 1;
    std::shared_ptr<MockUnderDampedEquationSolver> under_damped_equation_solver = std::make_shared<MockUnderDampedEquationSolver>();
    std::shared_ptr<MockOverDampedEquationSolver> over_damped_equation_solver = std::make_shared<MockOverDampedEquationSolver>();
    std::shared_ptr<MockCriticallyDampedEquationSolver> critically_damped_equation_solver = std::make_shared<MockCriticallyDampedEquationSolver>();
    calc::SecondOrderEquationSolverSelector equation_solver_selector{under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver};    
    MockOverDampedEquationSolver expected = MockOverDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector.select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}

TEST(EquationSolverFactoryTestSuite, ShouldReturnPointerToUnderDampedEquationSolver) {
    //given
    long double discriminant = -1;
    std::shared_ptr<MockUnderDampedEquationSolver> under_damped_equation_solver = std::make_shared<MockUnderDampedEquationSolver>();
    std::shared_ptr<MockOverDampedEquationSolver> over_damped_equation_solver = std::make_shared<MockOverDampedEquationSolver>();
    std::shared_ptr<MockCriticallyDampedEquationSolver> critically_damped_equation_solver = std::make_shared<MockCriticallyDampedEquationSolver>();
    calc::SecondOrderEquationSolverSelector equation_solver_selector{under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver};    
    MockUnderDampedEquationSolver expected = MockUnderDampedEquationSolver{};

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector.select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(expected));
}
