#include <cmath>

#include "equation_solver.hpp"
#include "solution.hpp"

calc::Solution* calc::EquationSolver::find_general_solution(double a, double b, double c) {
    long double discriminant = b*b - 4*a*c;

    if (discriminant == 0) {
        long double roots_real_part = -b/(2*a);
        calc::CriticallyDampedSolution * result = new calc::CriticallyDampedSolution{{roots_real_part, 0}, {roots_real_part, 0}};
        return result;
    } else if (discriminant > 0) {
        long double first_root_real_part = (-b - std::sqrt(discriminant))/(2*a);
        long double second_root_real_part = (-b + std::sqrt(discriminant))/(2*a);
        calc::OverDampedSolution * result = new calc::OverDampedSolution{{first_root_real_part, 0}, {second_root_real_part, 0}};
        return result;
    } else {
        long double roots_real_part = -b/(2*a);
        long double first_root_imaginary_part = -std::sqrt(-discriminant)/(2*a);
        long double second_root_imaginary_part = std::sqrt(-discriminant)/(2*a);
        calc::UnderDampedSolution * result = new calc::UnderDampedSolution{{roots_real_part, first_root_imaginary_part}, {roots_real_part, second_root_imaginary_part}};
        return result;
    }
}
