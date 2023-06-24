#include <memory>
#include <cmath>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/calc/equation_solver_selector.hpp"
#include "../../src/calc/equation_solver.hpp"

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

class EquationSolverSelectorTestSuite : public ::testing::Test {
protected:
    void SetUp() override {
        under_damped_equation_solver = std::make_shared<MockUnderDampedEquationSolver>();
        over_damped_equation_solver = std::make_shared<MockOverDampedEquationSolver>();
        critically_damped_equation_solver = std::make_shared<MockCriticallyDampedEquationSolver>();
        equation_solver_selector = std::make_shared<calc::SecondOrderEquationSolverSelector>(under_damped_equation_solver, over_damped_equation_solver, critically_damped_equation_solver);
    }
    std::shared_ptr<calc::SecondOrderEquationSolverSelector> equation_solver_selector;
    std::shared_ptr<MockUnderDampedEquationSolver> under_damped_equation_solver;
    std::shared_ptr<MockOverDampedEquationSolver> over_damped_equation_solver;
    std::shared_ptr<MockCriticallyDampedEquationSolver> critically_damped_equation_solver;
};

TEST_F(EquationSolverSelectorTestSuite, ShouldReturnPointerToCriticallyDampedEquationSolver) {
    //given
    long double discriminant = 0;

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector->select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(*critically_damped_equation_solver));
}

TEST_F(EquationSolverSelectorTestSuite, ShouldReturnPointerToOverDampedEquationSolver) {
    //given
    long double discriminant = 1;

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector->select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(*over_damped_equation_solver));
}

TEST_F(EquationSolverSelectorTestSuite, ShouldReturnPointerToUnderDampedEquationSolver) {
    //given
    long double discriminant = -1;

    //when
    std::shared_ptr<calc::EquationSolver> actual = equation_solver_selector->select_equation_solver(discriminant);

    //then
    EXPECT_EQ(typeid(*actual), typeid(*under_damped_equation_solver));
}
