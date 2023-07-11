#include <memory>
#include <string>
#include <stdexcept>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../libs/json.hpp"
#include "../../src/mapper/solution_mapper.hpp"
#include "../../src/calc/solution.hpp"

class MockSolution : public calc::Solution {
public:
    MOCK_METHOD(std::string, get_result_equation, (), (override));
    MOCK_METHOD(std::string, get_initial_equation, (), ());
protected:
    void validate_roots(const Root& first_root, const Root& second_root) {}
};

TEST(SolutionMapperTestSuite, ShouldFailAsSolutionTypeNotRecognized) {
    //given
    std::shared_ptr<MockSolution> solution = std::make_shared<MockSolution>();

    mapper::SolutionMapperImpl mapper{};

    //when
    try {
        std::string actual = mapper.serialize(solution);
        FAIL();
    } catch (const std::logic_error& e) {
        EXPECT_STREQ("Solution type not recognized", e.what());
    }
}

TEST(SolutionMapperTestSuite, ShouldSerializeUnderDampedSolution) {
    //given
    std::shared_ptr<calc::UnderDampedSolution> solution 
        = std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{{0, 1}, {0, -1}, 1, 1, "initial equation", 1});
    std::string expected = "{\"initialEquation\":\"initial equation\",\"maxAmplitudeExtremumAtT\":1.0,\"resultEquation\":\"x = (cos(t)+sin(t))\",\"solution\":{\"addend\":{\"argument\":1.0,\"coefficient\":1.0,\"type\":\"sin\"},\"augend\":{\"argument\":1.0,\"coefficient\":1.0,\"type\":\"cos\"},\"multiplier\":{\"argument\":0.0,\"coefficient\":1.0,\"type\":\"e\"}}}";
    mapper::SolutionMapperImpl mapper{};

    //when
    std::string actual = mapper.serialize(solution);

    //then
    EXPECT_EQ(expected, actual);
}

TEST(SolutionMapperTestSuite, ShouldSerializeOverDampedSolution) {
    //given
    std::shared_ptr<calc::OverDampedSolution> solution 
        = std::make_shared<calc::OverDampedSolution>(calc::OverDampedSolution{{-2, 0}, {-3, 0}, 1, 1, "initial equation", 1});
    std::string expected = "{\"initialEquation\":\"initial equation\",\"maxAmplitudeExtremumAtT\":1.0,\"resultEquation\":\"x = e^(-2t)+1e^(-3t)\",\"solution\":{\"addend\":{\"argument\":-3.0,\"coefficient\":1.0,\"type\":\"e\"},\"augend\":{\"argument\":-2.0,\"coefficient\":1.0,\"type\":\"e\"},\"multiplier\":{\"argument\":0.0,\"coefficient\":1.0,\"type\":\"e\"}}}";
    mapper::SolutionMapperImpl mapper{};

    //when
    std::string actual = mapper.serialize(solution);

    //then
    EXPECT_EQ(expected, actual);
}

TEST(SolutionMapperTestSuite, ShouldSerializeCriticallyDampedSolution) {
    //given
    std::shared_ptr<calc::CriticallyDampedSolution> solution 
        = std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{{-2, 0}, {-2, 0}, 1, 1, "initial equation", 1});
    std::string expected = "{\"initialEquation\":\"initial equation\",\"maxAmplitudeExtremumAtT\":1.0,\"resultEquation\":\"x = (1+t)*e^(-2t)\",\"solution\":{\"addend\":{\"argument\":1.0,\"coefficient\":1.0,\"type\":\"t\"},\"augend\":{\"argument\":0.0,\"coefficient\":1.0,\"type\":\"e\"},\"multiplier\":{\"argument\":-2.0,\"coefficient\":1.0,\"type\":\"e\"}}}";
    mapper::SolutionMapperImpl mapper{};

    //when
    std::string actual = mapper.serialize(solution);

    //then
    EXPECT_EQ(expected, actual);
}
