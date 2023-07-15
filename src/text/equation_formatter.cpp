#include "equation_formatter.hpp"

#include <sstream>
#include <string>

#include "../calc/solution.hpp"

std::string format_operand(const double& multiplier, const std::string& multiplicand, const bool& isEquationHead) {
    std::stringstream sstm{};

    if (multiplier == 1) {
        if (!isEquationHead) {
            sstm << "+";
        }
        sstm << multiplicand;
    } else if (multiplier == -1) {
        sstm << "-" << multiplicand;
    } else if (multiplier != 0) {
        if (multiplier > 0 && !isEquationHead) {
            sstm << "+";
        }
        sstm << multiplier << multiplicand;
    }

    return sstm.str();
}

std::string text::SecondOrderEquationFormatter::format_second_order(const double& a, const double& b, const double& c) {
    std::stringstream sstm{};

    sstm << format_operand(a, "x''", sstm.tellp() == std::streampos(0));
    sstm << format_operand(b, "x'", sstm.tellp() == std::streampos(0));
    sstm << format_operand(c, "x", sstm.tellp() == std::streampos(0));
    sstm << "=0";

    return sstm.str();
}

std::string text::SecondOrderEquationFormatter::format_under_damped_result(
            const long double& first_root_real_part, const long double& first_root_imaginary_part, const long double& coefficient_a, const long double& coefficient_b) {
    std::stringstream sstm{};
    sstm << "x = ";

    if (first_root_real_part) {
        if (first_root_real_part == 1) {
            sstm << "e^(t)*";
        } else if (first_root_real_part == -1) {
            sstm << "e^(-t)*";
        } else {
            sstm << "e^(" << first_root_real_part << "t)*";
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

        if (first_root_imaginary_part == 1) {
            sstm << "t)";
        } else if (first_root_imaginary_part == -1) {
            sstm << "-t)";
        } else {
            sstm << first_root_imaginary_part << "t)";
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

        if (first_root_imaginary_part == 1) {
            sstm << "t)";
        } else if (first_root_imaginary_part == -1) {
            sstm << "-t)";
        } else {
            sstm << first_root_imaginary_part << "t)";
        }
    }

    if (coefficient_a and coefficient_b) {
        sstm << ")";
    }

    return sstm.str();
}

std::string text::SecondOrderEquationFormatter::format_over_damped_result(
            const long double& first_root_real_part, const long double& second_root_real_part, const long double& coefficient_a, const long double& coefficient_b) {
    std::stringstream sstm{};
    sstm << "x = ";
    if (coefficient_a) {
        if (coefficient_a == -1) {
            sstm << "-";
        } else if (coefficient_a != 1) {
            sstm << coefficient_a;
        }

        if (first_root_real_part) {
            sstm << "e^";
            
            if (first_root_real_part == 1) {
                sstm << "(t)";
            } else if (first_root_real_part == -1) {
                sstm << "(-t)";
            } else {
                sstm << "(" << first_root_real_part << "t)";
            }
        }
    }

    if (coefficient_a and coefficient_b > 0) {
        sstm << "+";
    }

    if (coefficient_b) {
        sstm << coefficient_b;

        if (second_root_real_part) {
            sstm << "e^";
            
            if (second_root_real_part == 1) {
                sstm << "(t)";
            } else if (second_root_real_part == -1) {
                sstm << "(-t)";
            } else {
                sstm << "(" << second_root_real_part << "t)";
            }
        }
    }
    return sstm.str();
}

std::string text::SecondOrderEquationFormatter::format_critically_damped_result(
            const long double& first_root_real_part, const long double& coefficient_a, const long double& coefficient_b) {
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

    if (first_root_real_part) {
        sstm << "*e^(";

        if (first_root_real_part == 1) {
            sstm << "t)";
        } else if (first_root_real_part == -1) {
            sstm << "-t)";
        } else {
            sstm << first_root_real_part << "t)";
        }
    }
    return sstm.str();
}
