#include "solution.hpp"

#include <string>
#include <sstream>

calc::Solution::Solution(Root first_root, Root second_root) 
            : first_root{ first_root }, second_root{ second_root } 
            {}

calc::UnderDampedSolution::UnderDampedSolution(Root first_root, Root second_root) 
            : calc::Solution(first_root , second_root) 
            { validate_roots(first_root, second_root); }

calc::OverDampedSolution::OverDampedSolution(Root first_root, Root second_root) 
            : calc::Solution(first_root , second_root) 
            { validate_roots(first_root, second_root); }

calc::CriticallyDampedSolution::CriticallyDampedSolution(Root first_root, Root second_root) 
            : calc::Solution(first_root , second_root) 
            { validate_roots(first_root, second_root); }

calc::Solution::Root calc::Solution::get_first_root() {
    return first_root;
}

calc::Solution::Root calc::Solution::get_second_root() {
    return second_root;
}

void calc::Solution::set_coefficient_a(long double coefficient_value) {
    coefficient_a = coefficient_value;
}

void calc::Solution::set_coefficient_b(long double coefficient_value) {
    coefficient_b = coefficient_value;
}

bool calc::Solution::operator==(const calc::Solution& other) const {
    return first_root.real_part == other.first_root.real_part 
        and first_root.imaginary_part == other.first_root.imaginary_part 
        and second_root.real_part == other.second_root.real_part
        and second_root.imaginary_part == other.second_root.imaginary_part;
}

std::string calc::UnderDampedSolution::display_general() {
    std::stringstream sstm{};
    sstm << "x = e^(" << first_root.real_part << "*t)*(A*cos(" << first_root.imaginary_part << "*t)+B*sin(" << first_root.imaginary_part << "*t))";
    return sstm.str();
}

std::string calc::UnderDampedSolution::display_particular() {
    std::stringstream sstm{};
    sstm << "x = e^(" << first_root.real_part << "*t)*(" << coefficient_a << "*cos(" << first_root.imaginary_part << "*t)+" << coefficient_b << "*sin(" << first_root.imaginary_part << "*t))";
    return sstm.str();
}

void calc::UnderDampedSolution::validate_roots(calc::Solution::Root first_root, calc::Solution::Root second_root) {
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

std::string calc::OverDampedSolution::display_general() {
    std::stringstream sstm{};
    sstm << "x = A*e^(" << first_root.real_part << "*t) + B*e^(" << second_root.real_part << "*t)";
    return sstm.str();
}

std::string calc::OverDampedSolution::display_particular() {

}

void calc::OverDampedSolution::validate_roots(calc::Solution::Root first_root, calc::Solution::Root second_root) {
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

std::string calc::CriticallyDampedSolution::display_general() {
    std::stringstream sstm{};
    sstm << "x = (A + B*t)e^(" << first_root.real_part << "*t)";
    return sstm.str();
}

std::string calc::CriticallyDampedSolution::display_particular() {

}

void calc::CriticallyDampedSolution::validate_roots(calc::Solution::Root first_root, calc::Solution::Root second_root) {
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
