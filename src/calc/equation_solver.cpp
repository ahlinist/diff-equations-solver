#include "equation_solver.hpp"

#include <cmath>
#include <memory>

#include "solution.hpp"

std::unique_ptr<calc::Solution> calc::EquationSolver::find_general_solution(double a, double b, double c) {
    long double discriminant = b*b - 4*a*c;

    if (discriminant == 0) {
        long double roots_real_part = -b/(2*a);
        return std::make_unique<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{{roots_real_part, 0}, {roots_real_part, 0}});
    } else if (discriminant > 0) {
        long double first_root_real_part = (-b - std::sqrt(discriminant))/(2*a);
        long double second_root_real_part = (-b + std::sqrt(discriminant))/(2*a);
        return std::make_unique<calc::OverDampedSolution>(calc::OverDampedSolution{{first_root_real_part, 0}, {second_root_real_part, 0}});
    } else {
        long double roots_real_part = -b/(2*a);
        long double first_root_imaginary_part = std::sqrt(-discriminant)/(2*a);
        long double second_root_imaginary_part = -first_root_imaginary_part;
        return std::make_unique<calc::UnderDampedSolution>(calc::UnderDampedSolution{{roots_real_part, first_root_imaginary_part}, {roots_real_part, second_root_imaginary_part}});
    }
}
