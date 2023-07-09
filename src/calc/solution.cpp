#include "solution.hpp"

#include <string>
#include <sstream>

calc::Solution::Solution(
    const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation, const long double& max_at_t) 
            : first_root{ first_root }, second_root{ second_root }, coefficient_a{ coefficient_a }, coefficient_b{ coefficient_b }, initial_equation {initial_equation}, max_at_t{ max_at_t }
            {}

calc::UnderDampedSolution::UnderDampedSolution(
    const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation, const long double& max_at_t) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b, initial_equation, max_at_t) 
            { validate_roots(first_root, second_root); }

calc::OverDampedSolution::OverDampedSolution(
    const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation, const long double& max_at_t) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b, initial_equation, max_at_t) 
            { validate_roots(first_root, second_root); }

calc::CriticallyDampedSolution::CriticallyDampedSolution(
    const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation, const long double& max_at_t) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b, initial_equation, max_at_t) 
            { validate_roots(first_root, second_root); }

calc::Solution::Root calc::Solution::get_first_root() {
    return first_root;
}

calc::Solution::Root calc::Solution::get_second_root() {
    return second_root;
}

long double calc::Solution::get_coefficient_a() {
    return coefficient_a;
}

long double calc::Solution::get_coefficient_b() {
    return coefficient_b;
}

long double calc::Solution::get_max_at_t() {
    return max_at_t;
}

bool calc::Solution::operator==(const calc::Solution& other) const {
    long double rounding_difference = 1e-9; 

    return first_root.real_part == other.first_root.real_part 
        and first_root.imaginary_part == other.first_root.imaginary_part 
        and second_root.real_part == other.second_root.real_part
        and second_root.imaginary_part == other.second_root.imaginary_part
        and coefficient_a == other.coefficient_a
        and coefficient_b == other.coefficient_b
        and std::abs(max_at_t - other.max_at_t) < rounding_difference;
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

//TODO: move to a separate class to make Solution just a data holder
std::string calc::UnderDampedSolution::get_result_equation() {
    std::stringstream sstm{};
    sstm << "x = ";
    if (first_root.real_part) {
        if (first_root.real_part == 1) {
            sstm << "e^(t)*";
        } else if (first_root.real_part == -1) {
            sstm << "e^(-t)*";
        } else {
            sstm << "e^(" << first_root.real_part << "t)*";
        }
    }
    
    if (coefficient_a and coefficient_b) {
        sstm << "(";
    }

    if (coefficient_a) {
        if (coefficient_a == 1) {
            sstm << "cos(";
        } else if (coefficient_a == -1) {
            sstm << "-cos(";
        } else {
            sstm << coefficient_a << "cos(";
        }

        if (first_root.imaginary_part == 1) {
            sstm << "t)";
        } else if (first_root.imaginary_part == -1) {
            sstm << "-t)";
        } else {
            sstm << first_root.imaginary_part << "t)";
        }
    }

    if (coefficient_b) {
        if (coefficient_b == 1) {
            sstm << "+sin(";
        } else if (coefficient_b == -1) {
            sstm << "-sin(";
        } else {
            if (coefficient_b > 0 and coefficient_a) {
                sstm << "+";
            }
            sstm << coefficient_b << "sin(";
        }

        if (first_root.imaginary_part == 1) {
            sstm << "t)";
        } else if (first_root.imaginary_part == -1) {
            sstm << "-t)";
        } else {
            sstm << first_root.imaginary_part << "t)";
        }
    }

    if (coefficient_a and coefficient_b) {
        sstm << ")";
    }

    return sstm.str();
}

std::string calc::OverDampedSolution::get_result_equation() {
    std::stringstream sstm{};
    sstm << "x = ";
    if (coefficient_a) {
        if (coefficient_a == -1) {
            sstm << "-";
        } else if (coefficient_a != 1) {
            sstm << coefficient_a;
        }

        if (first_root.real_part) {
            sstm << "e^";
            
            if (first_root.real_part == 1) {
                sstm << "(t)";
            } else if (first_root.real_part == -1) {
                sstm << "(-t)";
            } else {
                sstm << "(" << first_root.real_part << "t)";
            }
        }
    }

    if (coefficient_a and coefficient_b > 0) {
        sstm << "+";
    }

    if (coefficient_b) {
        sstm << coefficient_b;

        if (second_root.real_part) {
            sstm << "e^";
            
            if (second_root.real_part == 1) {
                sstm << "(t)";
            } else if (second_root.real_part == -1) {
                sstm << "(-t)";
            } else {
                sstm << "(" << second_root.real_part << "t)";
            }
        }
    }
    return sstm.str();
}

std::string calc::CriticallyDampedSolution::get_result_equation() {
    std::stringstream sstm{};
    sstm << "x = ";

    if (coefficient_a and coefficient_b) {
        sstm << "(";
    }

    if (coefficient_a) {
        sstm << coefficient_a;

        if (coefficient_b > 0) {
            sstm << "+";
        }
    }

    if (coefficient_b) {
        if (coefficient_b == 1) {
            sstm << "t";
        } else if (coefficient_b == -1) {
            sstm << "-t";
        } else {
            sstm << coefficient_b << "t";
        }
    }

    if (coefficient_a and coefficient_b) {
        sstm << ")";
    }

    if (first_root.real_part) {
        sstm << "*e^(";

        if (first_root.real_part == 1) {
            sstm << "t)";
        } else if (first_root.real_part == -1) {
            sstm << "-t)";
        } else {
            sstm << first_root.real_part << "t)";
        }
    }
    return sstm.str();
}

std::string calc::Solution::get_initial_equation() {
    return initial_equation;
}
