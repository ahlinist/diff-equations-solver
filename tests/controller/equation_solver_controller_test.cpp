#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/controller/equation_solver_controller.hpp"
#include "../../src/service/equation_solver_service.hpp"
#include "../../src/calc/solution.hpp"
#include "../../libs/httplib.h"

class MockServer : public httplib::Server {
public:
    MOCK_METHOD(void, Get, (const char* pattern, const std::function<void(const httplib::Request&, httplib::Response&)>& handler), ());
};

class MockService : public service::EquationSolverService {
public:
    MOCK_METHOD(std::shared_ptr<calc::Solution>, solve_second_level, (const double&, const double&, const double&, const double&, const double&), (override));
};

class MockSolution : public calc::Solution {
public:
    MOCK_METHOD(std::string, display, (), (override));
protected:
    void validate_roots(const Root& first_root, const Root& second_root) {}
};

TEST(EquationControllerTestSuite, ShouldReceiveTheRequestAndReturnResponse) {
    //given
    std::shared_ptr<MockServer> server = std::make_shared<MockServer>();
    std::shared_ptr<MockService> equation_solver_service = std::make_shared<MockService>();
    std::shared_ptr<MockSolution> solution = std::make_shared<MockSolution>();

    controller::EquationSolverControllerImpl equation_solver_controller{server, equation_solver_service};

    //TODO: write proper tests when controllers and routers are separated

    //when
    equation_solver_controller.enable();
}
