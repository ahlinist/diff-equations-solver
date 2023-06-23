#ifndef INPUT_FORMATTER_HEADER
#define INPUT_FORMATTER_HEADER

#include <string>

namespace input {
    class InputFormatter {
    public:
        virtual ~InputFormatter() {}
        virtual std::string format_equation(double a, double b, double c) = 0;
    protected:
        std::string format_operand(double multiplier, std::string multiplicand, bool isEquationHead);
    };

    class SecondOrderInputFormatter : public InputFormatter {
    public:
        std::string format_equation(double a, double b, double c) override;
    };
}

#endif
