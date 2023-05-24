#ifndef INPUT_PARSER_HEADER
#define INPUT_PARSER_HEADER

#include <tuple>

namespace input {
    class InputParser {
    public:
        std::tuple<double, double, double> receive_input();
    };
}

#endif
