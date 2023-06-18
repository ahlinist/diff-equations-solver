#include "equation_solver.hpp"

#include <cmath>
#include <memory>

#include "solution.hpp"

std::shared_ptr<calc::Solution> calc::UnderDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double roots_real_part = -b/(2 * a);
    long double first_root_imaginary_part = std::sqrt(-discriminant)/(2 * a);
    long double second_root_imaginary_part = -first_root_imaginary_part;
    calc::Solution::Root first_root{roots_real_part, first_root_imaginary_part};
    calc::Solution::Root second_root{roots_real_part, second_root_imaginary_part};
    long double coefficient_a = initial_x;
    long double coefficient_b = (initial_x_prime - roots_real_part * initial_x)/first_root_imaginary_part;
    return std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{first_root, second_root, coefficient_a, coefficient_b});
}

std::shared_ptr<calc::Solution> calc::OverDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double first_root_real_part = (-b - std::sqrt(discriminant))/(2 * a);
    long double second_root_real_part = (-b + std::sqrt(discriminant))/(2 * a);
    calc::Solution::Root first_root{first_root_real_part, 0};
    calc::Solution::Root second_root{second_root_real_part, 0};
    long double coefficient_b = (initial_x_prime - first_root_real_part * initial_x)/(second_root_real_part - first_root_real_part);
    long double coefficient_a = initial_x - coefficient_b;
    return std::make_shared<calc::OverDampedSolution>(calc::OverDampedSolution{first_root, second_root, coefficient_a, coefficient_b});
}

std::shared_ptr<calc::Solution> calc::CriticallyDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double roots_real_part = -b/(2*a);
    calc::Solution::Root first_root{roots_real_part, 0};
    calc::Solution::Root second_root{roots_real_part, 0};
    long double coefficient_a = initial_x;
    long double coefficient_b = initial_x_prime - roots_real_part;
    return std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{first_root, second_root, coefficient_a, coefficient_b});
}
