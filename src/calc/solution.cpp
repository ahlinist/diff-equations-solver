#include "solution.hpp"

#include <string>
#include <sstream>

std::string calc::UnderDampedSolution::display() {
    std::stringstream sstm{};
    sstm << "x = e^(" << first_root.real_part << "*t)*A*cos(" << first_root.imaginary_part << "*t)+i*B*sin(" << first_root.imaginary_part << "*t)";
    return sstm.str();
}

std::string calc::OverDampedSolution::display() {
    std::stringstream sstm{};
    sstm << "x = A*e^(" << first_root.real_part << "*t) + B*e^(" << second_root.real_part << "*t)";
    return sstm.str();
}

std::string calc::CriticallyDampedSolution::display() {
    std::stringstream sstm{};
    sstm << "x = (A + B*t)e^(" << first_root.real_part << "*t)";
    return sstm.str();
}
