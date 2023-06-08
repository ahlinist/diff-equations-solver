#ifndef INPUT_PARSER_HEADER
#define INPUT_PARSER_HEADER

#include <tuple>

namespace input {
    class InputParser {
    public:
        std::tuple<double, double, double> receive_equation_coefficients();
        std::tuple<double, double> receive_initial_conditions();
    };
}

#endif
