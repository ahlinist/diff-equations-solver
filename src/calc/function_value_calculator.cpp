#include "function_value_calculator.hpp"

#include <cmath>
#include <memory>
#include <vector>
#include <stdexcept>

#include "solution.hpp"
#include "../model/domain_model.hpp"

const int OVER_DAMPED_DECAY_FACTOR = 1000;
const int UNDER_DAMPED_DECAY_FACTOR = 1000;
const int CRITICALLY_DAMPED_DECAY_FACTOR = 3000;
const int UNDAMPED_OSCILLATOR_PERIODS_COUNT = 3 * 2 * M_PI;
const float OVER_DAMPED_CONSTANT_AMPLITUDE_FACTOR = 0.000001;
const int GRAPH_DATA_POINTS_COUNT = 800;

long double calculate_under_damped_value(std::shared_ptr<calc::Solution> solution, const long double& time) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double exp_arg = solution->get_first_root().real_part * time;
    long double trig_arg = solution->get_first_root().imaginary_part * time;
    return std::exp(exp_arg) * (coefficient_a * std::cos(trig_arg) + coefficient_b * std::sin(trig_arg));
}

long double calculate_over_damped_value(std::shared_ptr<calc::Solution> solution, const long double& time) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double exp_arg_a = solution->get_first_root().real_part * time;
    long double exp_arg_b = solution->get_second_root().real_part * time;
    return coefficient_a * std::exp(exp_arg_a) + coefficient_b * std::exp(exp_arg_b);
}

long double calculate_critically_damped_value(std::shared_ptr<calc::Solution> solution, const long double& time) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double exp_arg = solution->get_first_root().real_part * time;
    return std::exp(exp_arg) * (coefficient_a + coefficient_b * time);
}

long double calc::SecondOrderFunctionValueCalculator::calculate_value_at_time(std::shared_ptr<calc::Solution> solution, const long double& time) {
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

long double calculate_under_damped_extremum_time(std::shared_ptr<calc::Solution> solution) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double real_root = solution->get_first_root().real_part;
    long double imaginary_root = solution->get_first_root().imaginary_part;
    
    long double arctan_numerator = coefficient_a * real_root + coefficient_b * imaginary_root;
    long double arctan_denominator = coefficient_a * imaginary_root - coefficient_b * real_root;
    long double max_amplitude_extremum_at_t = std::atan2(arctan_numerator , arctan_denominator) / imaginary_root;
    return max_amplitude_extremum_at_t < 0 ? max_amplitude_extremum_at_t + M_PI / imaginary_root : max_amplitude_extremum_at_t;
}

long double calculate_over_damped_extremum_time(std::shared_ptr<calc::Solution> solution) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double first_root = solution->get_first_root().real_part;
    long double second_root = solution->get_second_root().real_part;

    long double ln_arg = -(coefficient_a * first_root) / (coefficient_b * second_root);
    long double max_amplitude_extremum_at_t = 0;

    if (ln_arg > 0) {
        max_amplitude_extremum_at_t = std::log(ln_arg) / (second_root - first_root);
    }

    return max_amplitude_extremum_at_t >= 0 ? max_amplitude_extremum_at_t : 0;
}

long double calculate_critically_damped_extremum_time(std::shared_ptr<calc::Solution> solution) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double root = solution->get_first_root().real_part;

    double long max_amplitude_extremum_at_t = -(coefficient_a * root + coefficient_b) / (coefficient_b * root);
    return max_amplitude_extremum_at_t >= 0 ? max_amplitude_extremum_at_t : 0;
}

long double calculate_under_damped_value_at_infinity(std::shared_ptr<calc::Solution> solution) {
    if (!solution->get_first_root().real_part) {
        long double extremum_at = calculate_under_damped_extremum_time(solution);
        return calculate_under_damped_value(solution, extremum_at);
    } else {
        return 0;
    }
}

long double calculate_over_damped_value_at_infinity(std::shared_ptr<calc::Solution> solution) {
    if (!solution->get_first_root().real_part) {
        return solution->get_coefficient_a();
    } else if (!solution->get_second_root().real_part) {
        return solution->get_coefficient_b();
    } else {
        return 0;
    }
}

long double calculate_critically_damped_value_at_infinity(std::shared_ptr<calc::Solution> solution) {
    return 0;
}

long double calculate_value_at_inifnity(std::shared_ptr<calc::Solution> solution) {
    if (std::dynamic_pointer_cast<calc::UnderDampedSolution>(solution)) {
        return calculate_under_damped_value_at_infinity(solution);
    } else if (std::dynamic_pointer_cast<calc::OverDampedSolution>(solution)) {
        return calculate_over_damped_value_at_infinity(solution);
    } else if (std::dynamic_pointer_cast<calc::CriticallyDampedSolution>(solution)) {
        return calculate_critically_damped_value_at_infinity(solution);
    } else {
        throw std::logic_error("Solution type not recognized");
    }
}

long double calc::SecondOrderFunctionValueCalculator::calculate_max_amplitude(std::shared_ptr<calc::Solution> solution) {
    long double extremum_time{};

    if (std::dynamic_pointer_cast<calc::UnderDampedSolution>(solution)) {
        extremum_time = calculate_under_damped_extremum_time(solution);
    } else if (std::dynamic_pointer_cast<calc::OverDampedSolution>(solution)) {
        extremum_time = calculate_over_damped_extremum_time(solution);
    } else if (std::dynamic_pointer_cast<calc::CriticallyDampedSolution>(solution)) {
        extremum_time = calculate_critically_damped_extremum_time(solution);
    } else {
        throw std::logic_error("Solution type not recognized");
    }

    long double amplitude_at_extremum = abs(calculate_value_at_time(solution, extremum_time));
    long double amplitude_at_zero = abs(calculate_value_at_time(solution, 0));
    long double amplitude_at_infinity = abs(calculate_value_at_inifnity(solution));
    return std::max(amplitude_at_extremum, std::max(amplitude_at_zero, amplitude_at_infinity));
}

long double calculate_under_damped_decay_time(std::shared_ptr<calc::Solution> solution) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double first_root_real_part = solution->get_first_root().real_part;
    long double first_root_imaginary_part = solution->get_first_root().imaginary_part;

    if (!first_root_real_part) {
        return UNDAMPED_OSCILLATOR_PERIODS_COUNT / first_root_imaginary_part;
    } else {
        long double ln_arg = coefficient_a / (UNDER_DAMPED_DECAY_FACTOR * std::sqrt(coefficient_a * coefficient_a + coefficient_b * coefficient_b));
        return std::log(std::abs(ln_arg)) / first_root_real_part;
    }
}

long double calculate_over_damped_decay_time(std::shared_ptr<calc::Solution> solution, const long double& amplitude) {
    long double coefficient_a = solution->get_coefficient_a();
    long double coefficient_b = solution->get_coefficient_b();
    long double first_root_real_part = solution->get_first_root().real_part;
    long double second_root_real_part = solution->get_second_root().real_part;

    long double coefficient_by_greater_root{};
    long double coefficient_by_lesser_root{};
    long double greater_root{};
    long double lesser_root{};

    if (first_root_real_part > second_root_real_part) {
        greater_root = first_root_real_part;
        lesser_root = second_root_real_part;
        coefficient_by_greater_root = coefficient_a;
        coefficient_by_lesser_root = coefficient_b;
    } else {
        greater_root = second_root_real_part;
        lesser_root = first_root_real_part;
        coefficient_by_greater_root = coefficient_b;
        coefficient_by_lesser_root = coefficient_a;
    }

    long double ln_arg = amplitude / (coefficient_by_greater_root * OVER_DAMPED_DECAY_FACTOR);
    long double max_value = std::log(ln_arg) / greater_root;

    if (!max_value) {
        long double ln_arg = -OVER_DAMPED_CONSTANT_AMPLITUDE_FACTOR * coefficient_by_greater_root / coefficient_by_lesser_root;
        return std::log(abs(ln_arg)) / lesser_root;
    } else {
        return max_value;
    }
}

long double calculate_critically_damped_decay_time(std::shared_ptr<calc::Solution> solution, const long double& amplitude) {
    long double coefficient_b = solution->get_coefficient_b();
    long double first_root_real_part = solution->get_first_root().real_part;

    long double ln_arg = amplitude / (CRITICALLY_DAMPED_DECAY_FACTOR * coefficient_b);
        return std::log(ln_arg) / first_root_real_part;
}

long double calc::SecondOrderFunctionValueCalculator::calculate_decay_time(std::shared_ptr<calc::Solution> solution) {
    if (std::dynamic_pointer_cast<calc::UnderDampedSolution>(solution)) {
        return calculate_under_damped_decay_time(solution);
    } else if (std::dynamic_pointer_cast<calc::OverDampedSolution>(solution)) {
        return calculate_over_damped_decay_time(solution, calculate_max_amplitude(solution));
    } else if (std::dynamic_pointer_cast<calc::CriticallyDampedSolution>(solution)) {
        return calculate_critically_damped_decay_time(solution, calculate_max_amplitude(solution));
    } else {
        throw std::logic_error("Solution type not recognized");
    }
}

std::vector<model::FunctionDataPoint> calc::SecondOrderFunctionValueCalculator::calculate_function_values(std::shared_ptr<calc::Solution> solution) {
    long double decay_time = calculate_decay_time(solution);
    long double step_size = decay_time / GRAPH_DATA_POINTS_COUNT;
    std::vector<model::FunctionDataPoint> function_values{};

    for (int i = 0; i < GRAPH_DATA_POINTS_COUNT; i++) {
        long double time = i * step_size;
        long double value = calculate_value_at_time(solution, time);
        function_values.push_back(model::FunctionDataPoint{time, value});
    }

    return function_values;
}
