#include <memory>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/controller/equation_solver_controller.hpp"
#include "../../src/service/equation_solver_service.hpp"
#include "../../src/mapper/solution_mapper.hpp"
#include "../../src/input/input_validator.hpp"
#include "../../src/calc/solution.hpp"
#include "../../libs/httplib.h"

class MockService : public service::EquationSolverService {
public:
    MOCK_METHOD(std::shared_ptr<calc::Solution>, solve_second_order, (const double&, const double&, const double&, const double&, const double&), (override));
};

class MockSolution : public calc::Solution {
public:
    MOCK_METHOD(std::string, get_initial_equation, (), (override));
    MOCK_METHOD(std::string, get_result_equation, (), (override));
protected:
    void validate_roots(const Root& first_root, const Root& second_root) {}
};

class MockSolutionMapper : public mapper::SolutionMapper {
public:
    MOCK_METHOD(std::string, serialize, (std::shared_ptr<calc::Solution>), (override));
};

class MockInputValidator : public input::InputValidator {
public:
    MOCK_METHOD(void, validate_second_order, (const double&, const double&, const double&, const double&, const double&), (override));
};

TEST(EquationControllerTestSuite, ShouldReceiveTheRequestAndReturnResponse) {
    //given
    std::shared_ptr<MockInputValidator> input_validator = std::make_shared<MockInputValidator>();
    std::shared_ptr<MockService> equation_solver_service = std::make_shared<MockService>();
    std::shared_ptr<calc::Solution> solution = std::make_shared<MockSolution>();
    std::shared_ptr<MockSolutionMapper> mapper = std::make_shared<MockSolutionMapper>();
    std::string expected = "solution";

    controller::EquationSolverControllerImpl equation_solver_controller{ equation_solver_service, mapper, input_validator };

    EXPECT_CALL(*input_validator, validate_second_order(6.0, 7.0, 8.0, 9.0, 10.0));
    EXPECT_CALL(*equation_solver_service, solve_second_order(6.0, 7.0, 8.0, 9.0, 10.0))
        .WillOnce(::testing::Return(solution));
    EXPECT_CALL(*mapper, serialize(solution))
        .WillOnce(::testing::Return("solution"));

    //when
    std::string actual = equation_solver_controller.solve_second_order(6.0, 7.0, 8.0, 9.0, 10.0);

    //then
    EXPECT_EQ(expected, actual);
}
