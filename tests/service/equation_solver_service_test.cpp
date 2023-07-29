#include <memory>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/service/equation_solver_service.hpp"
#include "../../src/calc/equation_solver_selector.hpp"
#include "../../src/calc/solution.hpp"
#include "../../src/text/equation_formatter.hpp"
#include "../../src/calc/function_value_calculator.hpp"
#include "../../src/model/domain_model.hpp"

class MockEquationSolver : public calc::EquationSolver {
public:
    MOCK_METHOD(std::shared_ptr<calc::Solution>, solve, (const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime), (override));
};

class MockEquationSolverSelector : public calc::EquationSolverSelector {
public:
    MOCK_METHOD(std::shared_ptr<calc::EquationSolver>, select_equation_solver, (const long double&), (override));
};

class MockSolution : public calc::Solution {
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) {}
};

class MockEquationFormatter : public text::EquationFormatter {
public:
    MOCK_METHOD(std::string, format_second_order_equation, (const double&, const double&, const double&), (override));
    MOCK_METHOD(std::string, format_second_order_solution, (std::shared_ptr<calc::Solution>), (override));
};

class MockFunctionValueCalculator : public calc::FunctionValueCalculator {
protected:
    MOCK_METHOD(long double, calculate_max_amplitude, (std::shared_ptr<calc::Solution>), (override));
    MOCK_METHOD(long double, calculate_decay_time, (std::shared_ptr<calc::Solution>), (override));
public:
    MOCK_METHOD(std::vector<model::FunctionDataPoint>, calculate_function_values, (std::shared_ptr<calc::Solution>), (override));
    MOCK_METHOD(long double, calculate_value_at_time, (std::shared_ptr<calc::Solution>, const long double&), (override)); 
};

TEST(EquationServiceTestSuite, ShouldSolveTheEquationAndReturnTheSolution) {
    //given
    std::shared_ptr<MockEquationSolverSelector> equation_solver_selector = std::make_shared<MockEquationSolverSelector>();
    std::shared_ptr<MockEquationSolver> equation_solver = std::make_shared<MockEquationSolver>();
    std::shared_ptr<MockEquationFormatter> equation_formatter = std::make_shared<MockEquationFormatter>(); 
    std::shared_ptr<MockFunctionValueCalculator> function_value_calculator = std::make_shared<MockFunctionValueCalculator>();
    std::shared_ptr<calc::Solution> solution = std::make_shared<MockSolution>();
    std::string initial_equation = "initial equation";
    std::string result_equation = "result equation";
    std::vector<model::FunctionDataPoint> data_points { {0, 1}, {1, 2} , {2, 3} };
    model::SolvedSecondOrderEquation expected{ initial_equation, result_equation, data_points };

    service::EquationSolverServiceImpl equation_solver_service{equation_solver_selector, equation_formatter, function_value_calculator};

    EXPECT_CALL(*equation_solver_selector, select_equation_solver(-143.0))
        .WillOnce(::testing::Return(equation_solver));
    EXPECT_CALL(*equation_solver, solve(-143, 6.0, 7.0, 8.0, 9.0, 10.0))
        .WillOnce(::testing::Return(solution));
    EXPECT_CALL(*equation_formatter, format_second_order_equation(6.0, 7.0, 8.0))
        .WillOnce(::testing::Return(initial_equation));
    EXPECT_CALL(*equation_formatter, format_second_order_solution(solution))
        .WillOnce(::testing::Return(result_equation));
    EXPECT_CALL(*function_value_calculator, calculate_function_values(solution))
        .WillOnce(::testing::Return(data_points));

    //when
    model::SolvedSecondOrderEquation actual = equation_solver_service.solve_second_order(6, 7, 8, 9, 10);

    //then
    EXPECT_EQ(expected, actual);
}
