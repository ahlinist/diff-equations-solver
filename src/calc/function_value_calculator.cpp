#include "function_value_calculator.hpp"

#include <cmath>
#include <memory>
#include <stdexcept>

#include "solution.hpp"

long double calculate_under_damped_value(std::shared_ptr<calc::Solution> solution, const double& time) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double exp_arg = solution->get_first_root().real_part * time;
    long double trig_arg = solution->get_first_root().imaginary_part * time;
    return std::exp(exp_arg) * (coefficient_a * std::cos(trig_arg) + coefficient_b * std::sin(trig_arg));
}

long double calculate_over_damped_value(std::shared_ptr<calc::Solution> solution, const double& time) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double exp_arg_a = solution->get_first_root().real_part * time;
    long double exp_arg_b = solution->get_second_root().real_part * time;
    return coefficient_a * std::exp(exp_arg_a) + coefficient_b * std::exp(exp_arg_b);
}

long double calculate_critically_damped_value(std::shared_ptr<calc::Solution> solution, const double& time) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double exp_arg = solution->get_first_root().real_part * time;
    return std::exp(exp_arg) * (coefficient_a + coefficient_b * time);
}

long double calc::SecondOrderFunctionValueCalculator::calculate_value_at(std::shared_ptr<calc::Solution> solution, const double& time) {
    if (std::dynamic_pointer_cast<calc::UnderDampedSolution>(solution)) {
        return calculate_under_damped_value(solution, time);
    } else if (std::dynamic_pointer_cast<calc::OverDampedSolution>(solution)) {
        return calculate_over_damped_value(solution, time);
    } else if (std::dynamic_pointer_cast<calc::CriticallyDampedSolution>(solution)) {
        return calculate_critically_damped_value(solution, time);
    } else {
        throw std::logic_error("Solution type not recognized");
    }
}
