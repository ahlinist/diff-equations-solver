#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/service/equation_solver_service.hpp"
#include "../../src/calc/equation_solver_selector.hpp"
#include "../../src/calc/solution.hpp"

class MockEquationSolver : public calc::EquationSolver {
public:
    MOCK_METHOD(std::shared_ptr<calc::Solution>, solve, (const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime), (override));
};

class MockEquationSolverSelector : public calc::EquationSolverSelector {
public:
    MOCK_METHOD(std::shared_ptr<calc::EquationSolver>, select_equation_solver, (const long double&), (override));
};

class MockSolution : public calc::Solution {
    public:
        MOCK_METHOD(std::string, display, (), (override));
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) {}
};

TEST(EquationServiceTestSuite, ShouldSolveTheEquationAndReturnTheSolution) {
    //given
    std::shared_ptr<MockEquationSolverSelector> equation_solver_selector = std::make_shared<MockEquationSolverSelector>();
    std::shared_ptr<MockEquationSolver> equation_solver = std::make_shared<MockEquationSolver>();
    std::shared_ptr<MockSolution> expected = std::make_shared<MockSolution>();

    service::EquationSolverServiceImpl equation_solver_service{equation_solver_selector};

    EXPECT_CALL(*equation_solver_selector, select_equation_solver(-143.0))
        .WillOnce(::testing::Return(equation_solver));
    EXPECT_CALL(*equation_solver, solve(-143, 6.0, 7.0, 8.0, 9.0, 10.0))
        .WillOnce(::testing::Return(expected));

    //when
    std::shared_ptr<calc::Solution> solution = equation_solver_service.solve_second_level(6, 7, 8, 9, 10);

    //then
    EXPECT_EQ(expected, solution);
}
