#include "domain_model.hpp"

#include <cmath>

static constexpr long double precision = 1e-5;

bool model::FunctionDataPoint::operator==(const FunctionDataPoint& other) const {
    return (std::abs(time - other.time) <= precision) &&
        (std::abs(value - other.value) <= precision);
}

bool model::SolvedSecondOrderEquation::operator==(const SolvedSecondOrderEquation& other) const {
    return initial_equation == other.initial_equation
        and solution_equation == other.solution_equation
        and function_data_points == other.function_data_points;
}
