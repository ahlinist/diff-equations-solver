#include "input_formatter.hpp"

#include <sstream>
#include <string>

std::string input::InputFormatter::format_operand(double multiplier, std::string multiplicand, bool isEquationHead) {
    std::stringstream sstm{};

    if (multiplier == 1) {
        if (!isEquationHead) {
            sstm << "+";
        }
        sstm << multiplicand;
    } else if (multiplier != 0) {
        if (multiplier > 0 && !isEquationHead) {
            sstm << "+";
        }
        sstm << multiplier << multiplicand;
    }

    return sstm.str();
}

std::string input::InputFormatter::format_equation(double a, double b, double c) {
    std::stringstream sstm{};

    sstm << format_operand(a, "x''", sstm.tellp() == std::streampos(0));
    sstm << format_operand(b, "x'", sstm.tellp() == std::streampos(0));
    sstm << format_operand(c, "x", sstm.tellp() == std::streampos(0));
    sstm << "=0";

    return sstm.str();
}
