#include "solution.hpp"

#include <string>
#include <sstream>

calc::Solution::Solution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b) 
            : first_root{ first_root }, second_root{ second_root }, coefficient_a{ coefficient_a }, coefficient_b{ coefficient_b }
            {}

calc::UnderDampedSolution::UnderDampedSolution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b) 
            { validate_roots(first_root, second_root); }

calc::OverDampedSolution::OverDampedSolution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b) 
            { validate_roots(first_root, second_root); }

calc::CriticallyDampedSolution::CriticallyDampedSolution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b) 
            : calc::Solution(first_root , second_root, coefficient_a, coefficient_b) 
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

bool calc::Solution::operator==(const calc::Solution& other) const {
    return first_root.real_part == other.first_root.real_part 
        and first_root.imaginary_part == other.first_root.imaginary_part 
        and second_root.real_part == other.second_root.real_part
        and second_root.imaginary_part == other.second_root.imaginary_part
        and coefficient_a == other.coefficient_a
        and coefficient_b == other.coefficient_b;
}

std::string calc::UnderDampedSolution::display_general() {
    std::stringstream sstm{};
    sstm << "x = e^(" << first_root.real_part << "*t)*(A*cos(" << first_root.imaginary_part << "*t)+B*sin(" << first_root.imaginary_part << "*t))";
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

std::string calc::UnderDampedSolution::display_particular() {
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

std::string calc::OverDampedSolution::display_particular() {
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

std::string calc::CriticallyDampedSolution::display_particular() {
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
