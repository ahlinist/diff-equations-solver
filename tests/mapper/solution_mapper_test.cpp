#include <string>

#include <gtest/gtest.h>

#include "../../src/mapper/solution_mapper.hpp"
#include "../../src/model/domain_model.hpp"

TEST(SolutionMapperTestSuite, ShouldSerializeUnderDampedSolution) {
    //given
    std::vector<model::FunctionDataPoint> function_data_points{{0, 1}, {1, 3}, {2, 9}};
    model::SolvedSecondOrderEquation solved_solution{"initial equation", "result equation", function_data_points};
    std::string expected = "{\"functionDataPoints\":[{\"t\":0.0,\"y\":1.0},{\"t\":1.0,\"y\":3.0},{\"t\":2.0,\"y\":9.0}],\"initialEquation\":\"initial equation\",\"resultEquation\":\"result equation\"}";
    mapper::SolutionMapperImpl mapper{};

    //when
    std::string actual = mapper.serialize(solved_solution);

    //then
    EXPECT_EQ(expected, actual);
}
