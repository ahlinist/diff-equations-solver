#ifndef INPUT_FORMATTER_HEADER
#define INPUT_FORMATTER_HEADER

#include <string>

namespace input {
    class InputFormatter {
    public:
        std::string format_equation(double a, double b, double c);
    private:
        std::string format_operand(double multiplier, std::string multiplicand, bool isEquationHead);
    };
}

#endif
