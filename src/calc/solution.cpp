#include "solution.hpp"

#include <string>
#include <sstream>

calc::Solution::Solution(
    const Root& first_root, 
    const Root& second_root, 
    const long double& coefficient_a, 
    const long double& coefficient_b, 
    const std::string& initial_equation,
    const std::string& result_equation, 
    const long double& max_amplitude_extremum_at_t) 
            :   first_root{ first_root }, 
                second_root{ second_root }, 
                coefficient_a{ coefficient_a }, 
                coefficient_b{ coefficient_b }, 
                initial_equation { initial_equation }, 
                result_equation { result_equation },
                max_amplitude_extremum_at_t{ max_amplitude_extremum_at_t } {}

calc::UnderDampedSolution::UnderDampedSolution(
    const Root& first_root, 
    const Root& second_root, 
    const long double& coefficient_a, 
    const long double& coefficient_b, 
    const std::string& initial_equation, 
    const std::string& result_equation, 
    const long double& max_amplitude_extremum_at_t) 
            :  calc::Solution(first_root , second_root, coefficient_a, coefficient_b, initial_equation, result_equation, max_amplitude_extremum_at_t) 
            { validate_roots(first_root, second_root); }

calc::OverDampedSolution::OverDampedSolution(
    const Root& first_root, 
    const Root& second_root, 
    const long double& coefficient_a, 
    const long double& coefficient_b, 
    const std::string& initial_equation, 
    const std::string& result_equation, 
    const long double& max_amplitude_extremum_at_t) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b, initial_equation, result_equation, max_amplitude_extremum_at_t) 
            { validate_roots(first_root, second_root); }

calc::CriticallyDampedSolution::CriticallyDampedSolution(
    const Root& first_root, 
    const Root& second_root, 
    const long double& coefficient_a, 
    const long double& coefficient_b, 
    const std::string& initial_equation,
    const std::string& result_equation, 
    const long double& max_amplitude_extremum_at_t) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b, initial_equation, result_equation, max_amplitude_extremum_at_t) 
            { validate_roots(first_root, second_root); }

calc::Solution::Root calc::Solution::get_first_root() const {
    return first_root;
}

calc::Solution::Root calc::Solution::get_second_root() const {
    return second_root;
}

long double calc::Solution::get_coefficient_a() const {
    return coefficient_a;
}

long double calc::Solution::get_coefficient_b() const {
    return coefficient_b;
}

std::string calc::Solution::get_initial_equation() {
    return initial_equation;
}

std::string calc::Solution::get_result_equation() {
    return result_equation;
}

long double calc::Solution::get_max_amplitude_extremum_at_t() {
    return max_amplitude_extremum_at_t;
}

bool calc::Solution::operator==(const calc::Solution& other) const {
    long double rounding_difference = 1e-9; 

    return first_root.real_part == other.first_root.real_part 
        and first_root.imaginary_part == other.first_root.imaginary_part 
        and second_root.real_part == other.second_root.real_part
        and second_root.imaginary_part == other.second_root.imaginary_part
        and coefficient_a == other.coefficient_a
        and coefficient_b == other.coefficient_b
        and std::abs(max_amplitude_extremum_at_t - other.max_amplitude_extremum_at_t) < rounding_difference;
}

void calc::UnderDampedSolution::validate_roots(const calc::Solution::Root& first_root, const calc::Solution::Root& second_root) {
    std::string error_message{};
    
    if (first_root.real_part != second_root.real_part) {
        error_message += "Real parts of roots are different!\n";
    }
    if (first_root.imaginary_part != -second_root.imaginary_part) {
        error_message += "Values of roots imaginary parts are not opposite!\n";
    }

    if (error_message.size()) {
        throw std::invalid_argument(error_message);
    }
}

void calc::OverDampedSolution::validate_roots(const calc::Solution::Root& first_root, const calc::Solution::Root& second_root) {
    std::string error_message{};
    
    if (first_root.imaginary_part != 0 or second_root.imaginary_part != 0) {
        error_message += "Roots contain imaginary parts!\n";
    }
    if (first_root.real_part == second_root.real_part) {
        error_message += "Real parts are the same!\n";
    }

    if (error_message.size()) {
        throw std::invalid_argument(error_message);
    }
}

void calc::CriticallyDampedSolution::validate_roots(const calc::Solution::Root& first_root, const calc::Solution::Root& second_root) {
    std::string error_message{};
    
    if (first_root.imaginary_part != 0 or second_root.imaginary_part != 0) {
        error_message += "Roots contain imaginary parts!\n";
    }
    if (first_root.real_part != second_root.real_part) {
        error_message += "Real parts are not the same!\n";
    }

    if (error_message.size()) {
        throw std::invalid_argument(error_message);
    }
}
