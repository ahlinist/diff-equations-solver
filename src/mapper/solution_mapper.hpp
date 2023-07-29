#pragma once

#include <string>
#include <vector>
#include <map>

#include "../calc/solution.hpp"
#include "../model/domain_model.hpp"

namespace mapper {
    struct SecondOrderSolutionDto {
        std::string initialEquation{};
        std::string resultEquation{};
        std::vector<std::map<std::string, long double>> functionDataPoints{};
    };

    class SolutionMapper {
    public:
        virtual ~SolutionMapper() {}
        virtual std::string serialize(model::SolvedSecondOrderEquation solved_equation) = 0;
    };

    class SolutionMapperImpl : public SolutionMapper {
    public:
        std::string serialize(model::SolvedSecondOrderEquation solved_equation) override;
    };
}
