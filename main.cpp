#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

std::tuple<double, double, double> receive_input();
std::string format_operand(double multiplier, std::string multiplicand, bool isEquationHead);
std::string format_equation(double a, double b, double c);

int main() {
    auto [a, b, c] = receive_input();
    std::string equation = format_equation(a, b, c);

    std::cout << "The equation to be solved: " << equation << "=0" << std::endl;

    long double discriminant = b*b - 4*a*c;
    std::cout << "discriminant: " << discriminant << std::endl;
}

std::tuple<double, double, double> receive_input() {
    std::cout << "Greetings at differential equations solver. I can solve linear homogenous differential equations of 2-nd order: a*x''+b*x'+c*x=0" << std::endl;
    std::cout << "Please enter a, b and c." << std::endl;
    double a{}, b{}, c{};
    std::cout << "a=";
    std::cin >> a;
    std::cout << "b=";
    std::cin >> b;
    std::cout << "c=";
    std::cin >> c;
    return std::tuple{a, b, c};
}

std::string format_operand(double multiplier, std::string multiplicand, bool isEquationHead) {
    std::stringstream sstm{};

    if (multiplier == 1) {
        if (!isEquationHead) {
            sstm << "+";
        }
        
        sstm << multiplicand;
    } else if (multiplier != 0) {
        if (multiplier < 0) {
            sstm << "-";
        } else {
            if (!isEquationHead) {
                sstm << "+";
            }
        }
        sstm << multiplier << multiplicand;
    }

    return sstm.str();
}

std::string format_equation(double a, double b, double c) {
    std::stringstream sstm{};

    sstm << format_operand(a, "x''", sstm.tellp() == std::streampos(0));
    sstm << format_operand(b, "x'", sstm.tellp() == std::streampos(0));
    sstm << format_operand(c, "x", sstm.tellp() == std::streampos(0));

    return sstm.str();
}
