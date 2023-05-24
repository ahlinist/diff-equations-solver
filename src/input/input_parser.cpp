#include <tuple>
#include <iostream>

#include "input_parser.hpp"

std::tuple<double, double, double> input::InputParser::receive_input() {
    std::cout << "Greetings at differential equations solver. I can solve linear homogenous differential equations of 2-nd order: a*x''+b*x'+c*x=0" << std::endl;
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
