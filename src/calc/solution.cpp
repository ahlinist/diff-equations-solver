#include "solution.hpp"

#include <string>
#include <sstream>

calc::Solution::Solution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b) 
    : first_root{ first_root }, second_root{ second_root }, coefficient_a{ coefficient_a }, coefficient_b{ coefficient_b } {}

calc::UnderDampedSolution::UnderDampedSolution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b) 
    : calc::Solution(first_root , second_root, coefficient_a, coefficient_b) 
    { validate_roots(first_root, second_root); }

calc::OverDampedSolution::OverDampedSolution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b) 
    : calc::Solution(first_root , second_root, coefficient_a, coefficient_b) { validate_roots(first_root, second_root); }

calc::CriticallyDampedSolution::CriticallyDampedSolution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b) 
    : calc::Solution(first_root , second_root, coefficient_a, coefficient_b) { validate_roots(first_root, second_root); }

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

bool calc::Solution::operator==(const calc::Solution& other) const {
    return first_root.real_part == other.first_root.real_part 
        and first_root.imaginary_part == other.first_root.imaginary_part 
        and second_root.real_part == other.second_root.real_part
        and second_root.imaginary_part == other.second_root.imaginary_part
        and coefficient_a == other.coefficient_a
        and coefficient_b == other.coefficient_b;
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
