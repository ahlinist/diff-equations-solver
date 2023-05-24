#include <iostream>
#include <string>

#include "input/input_parser.hpp"
#include "input/input_formatter.hpp"

int main() {
    input::InputParser input_parser;
    auto [a, b, c] = input_parser.receive_input();

    input::InputFormatter input_formatter;
    std::string equation = input_formatter.format_equation(a, b, c);

    std::cout << "The equation to be solved: " << equation << "=0" << std::endl;

    //to be dealt with later
    long double discriminant = b*b - 4*a*c;
    std::cout << "discriminant: " << discriminant << std::endl;
}
