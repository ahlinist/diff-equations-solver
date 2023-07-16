#pragma once

#include <string>
#include <memory>
#include <map>

#include "../calc/solution.hpp"

namespace mapper {
    struct Term {
        long double coefficient{};
        std::string type{};
        long double argument{};
    };

    struct Solution {
        Term multiplier{};
        Term augend{};
        Term addend{};
    };

    struct Response {
        std::string initialEquation{};
        std::string resultEquation{};
        Solution solution{};
        long double maxAmplitudeExtremumAtT{};
        long double decaysAtT{};
    };

    class SolutionMapper {
    public:
        virtual ~SolutionMapper() {}
        virtual std::string serialize(std::shared_ptr<calc::Solution> solution) = 0;
    };

    class SolutionMapperImpl : public SolutionMapper {
    public:
        std::string serialize(std::shared_ptr<calc::Solution> solution) override;
    };
}
