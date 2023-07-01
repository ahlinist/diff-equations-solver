#include <memory>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/controller/equation_solver_controller.hpp"
#include "../../src/service/equation_solver_service.hpp"
#include "../../src/calc/solution.hpp"
#include "../../libs/httplib.h"

class MockService : public service::EquationSolverService {
public:
    MOCK_METHOD(std::shared_ptr<calc::Solution>, solve_second_order, (const double&, const double&, const double&, const double&, const double&), (override));
};

class MockSolution : public calc::Solution {
public:
    MOCK_METHOD(std::string, display, (), (override));
protected:
    void validate_roots(const Root& first_root, const Root& second_root) {}
};

TEST(EquationControllerTestSuite, ShouldReceiveTheRequestAndReturnResponse) {
    //given
    std::shared_ptr<MockService> equation_solver_service = std::make_shared<MockService>();
    std::shared_ptr<MockSolution> solution = std::make_shared<MockSolution>();
    std::string expected = "solution";

    controller::EquationSolverControllerImpl equation_solver_controller{ equation_solver_service };

    EXPECT_CALL(*equation_solver_service, solve_second_order(6.0, 7.0, 8.0, 9.0, 10.0))
        .WillOnce(::testing::Return(solution));
    EXPECT_CALL(*solution, display())
        .WillOnce(::testing::Return("solution"));

    //when
    std::string actual = equation_solver_controller.solve_second_order(6.0, 7.0, 8.0, 9.0, 10.0);

    //then
    EXPECT_EQ(expected, actual);
}
