#pragma once

#include <string>
#include <vector>

namespace model {
    struct FunctionDataPoint {
        long double time{};
        long double value{};

        bool operator==(const FunctionDataPoint& other) const;
    };

    struct SolvedSecondOrderEquation {
        std::string initial_equation{};
        std::string solution_equation{};
        std::vector<model::FunctionDataPoint> function_data_points{};

        bool operator==(const SolvedSecondOrderEquation& other) const;
    };
}
