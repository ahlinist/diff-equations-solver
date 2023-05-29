#include "input_parser.hpp"

#include <tuple>
#include <iostream>

std::tuple<double, double, double> input::InputParser::receive_input() {
    std::cout << "Please enter a, b and c." << std::endl;
    double a{}, b{}, c{};
    std::cout << "a=";
    std::cin >> a;
    std::cout << "b=";
    std::cin >> b;
    std::cout << "c=";
    std::cin >> c;
    return std::tuple<double, double, double>{a, b, c};
} 
