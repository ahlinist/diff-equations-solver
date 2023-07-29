#include <memory>
#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/controller/equation_solver_controller.hpp"
#include "../../src/service/equation_solver_service.hpp"
#include "../../src/mapper/solution_mapper.hpp"
#include "../../src/input/input_validator.hpp"
#include "../../src/model/domain_model.hpp"

class MockService : public service::EquationSolverService {
public:
    MOCK_METHOD(model::SolvedSecondOrderEquation, solve_second_order, (const double&, const double&, const double&, const double&, const double&), (override));
};

class MockSolutionMapper : public mapper::SolutionMapper {
public:
    MOCK_METHOD(std::string, serialize, (model::SolvedSecondOrderEquation), (override));
};

class MockInputValidator : public input::InputValidator {
public:
    MOCK_METHOD(void, validate_second_order, (const double&, const double&, const double&, const double&, const double&), (override));
};

TEST(EquationControllerTestSuite, ShouldReceiveTheRequestAndReturnResponse) {
    //given
    std::shared_ptr<MockInputValidator> input_validator = std::make_shared<MockInputValidator>();
    std::shared_ptr<MockService> equation_solver_service = std::make_shared<MockService>();
    std::shared_ptr<MockSolutionMapper> mapper = std::make_shared<MockSolutionMapper>();
    std::vector<model::FunctionDataPoint> function_data_points{{0, 2}, {3, 11}};
    model::SolvedSecondOrderEquation solved_equation{"initial equation", "solved_equation", function_data_points};
    std::string expected = "solution";

    controller::EquationSolverControllerImpl equation_solver_controller{ equation_solver_service, mapper, input_validator };

    EXPECT_CALL(*input_validator, validate_second_order(6.0, 7.0, 8.0, 9.0, 10.0));
    EXPECT_CALL(*equation_solver_service, solve_second_order(6.0, 7.0, 8.0, 9.0, 10.0))
        .WillOnce(::testing::Return(solved_equation));
    EXPECT_CALL(*mapper, serialize(solved_equation))
        .WillOnce(::testing::Return("solution"));

    //when
    std::string actual = equation_solver_controller.solve_second_order(6.0, 7.0, 8.0, 9.0, 10.0);

    //then
    EXPECT_EQ(expected, actual);
}
