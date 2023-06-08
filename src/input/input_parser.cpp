#include "input_parser.hpp"

#include <tuple>
#include <iostream>

std::tuple<double, double, double> input::InputParser::receive_equation_coefficients() {
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

std::tuple<double, double> input::InputParser::receive_initial_conditions() {
    std::cout << "Please enter initial conditions: x(0) = ?, x'(0) = ?." << std::endl;
    double initial_x{}, initial_x_prime{};
    std::cout << "x(0)=";
    std::cin >> initial_x;
    std::cout << "x'(0)=";
    std::cin >> initial_x_prime;
    return std::tuple<double, double>{initial_x, initial_x_prime};
}