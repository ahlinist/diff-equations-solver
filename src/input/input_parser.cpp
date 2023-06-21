#include "input_parser.hpp"

#include <tuple>
#include <iostream>

std::tuple<double, double, double, double, double> input::ConsoleInputParser::receive_input() {
    std::cout << "Please enter a, b and c." << std::endl;
    double a{}, b{}, c{}, initial_x{}, initial_x_prime{};
    std::cout << "a=";
    std::cin >> a;
    std::cout << "b=";
    std::cin >> b;
    std::cout << "c=";
    std::cin >> c;
    std::cout << "x(0)=";
    std::cin >> initial_x;
    std::cout << "x'(0)=";
    std::cin >> initial_x_prime;
    return std::tuple<double, double, double, double, double>{a, b, c, initial_x, initial_x_prime};
} 
