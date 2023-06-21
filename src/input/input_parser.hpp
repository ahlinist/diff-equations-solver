#ifndef INPUT_PARSER_HEADER
#define INPUT_PARSER_HEADER

#include <tuple>

namespace input {
    class InputParser {
    public:
        virtual ~InputParser() {}
        virtual std::tuple<double, double, double, double, double> receive_input() = 0;
    };

    class ConsoleInputParser : public InputParser {
    public:
        std::tuple<double, double, double, double, double> receive_input() override;
    };
}

#endif
