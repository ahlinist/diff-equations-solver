#include "equation_solver.hpp"

#include <cmath>
#include <memory>

#include "solution.hpp"

calc::EquationSolver::EquationSolver(const std::shared_ptr<input::InputFormatter> input_formatter) : input_formatter{ input_formatter } {}

std::shared_ptr<calc::Solution> calc::UnderDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double roots_real_part = -b/(2 * a);
    long double first_root_imaginary_part = std::sqrt(-discriminant)/(2 * a);
    calc::Solution::Root first_root{roots_real_part, first_root_imaginary_part};
    calc::Solution::Root second_root{roots_real_part, -first_root_imaginary_part};
    long double coefficient_a = initial_x;
    long double coefficient_b = (initial_x_prime - roots_real_part * initial_x) * first_root_imaginary_part;
    std::string initial_equation = input_formatter->format_equation(a, b, c);
    long double max_amplitude_extremum_at_t = calculate_max_amplitude_extremum_at_t(first_root, coefficient_a, coefficient_b);
    return std::make_shared<calc::UnderDampedSolution>(
        calc::UnderDampedSolution{first_root, second_root, coefficient_a, coefficient_b, initial_equation, max_amplitude_extremum_at_t});
}

long double calc::UnderDampedEquationSolver::calculate_max_amplitude_extremum_at_t(
        const calc::Solution::Root& first_root, const long double& coefficient_a, const long double& coefficient_b) {
    long double arctan_numerator = coefficient_a * first_root.real_part + coefficient_b * first_root.imaginary_part;
    long double arctan_denominator = coefficient_a * first_root.imaginary_part - coefficient_b * first_root.real_part;
    long double max_amplitude_extremum_at_t = std::atan2(arctan_numerator , arctan_denominator) / first_root.imaginary_part;
    return max_amplitude_extremum_at_t < 0 ? max_amplitude_extremum_at_t + M_PI / first_root.imaginary_part : max_amplitude_extremum_at_t;
}

std::shared_ptr<calc::Solution> calc::OverDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double first_root_real_part = (-b - std::sqrt(discriminant))/(2 * a);
    long double second_root_real_part = (-b + std::sqrt(discriminant))/(2 * a);
    calc::Solution::Root first_root{first_root_real_part, 0};
    calc::Solution::Root second_root{second_root_real_part, 0};
    long double coefficient_b = (initial_x_prime - first_root_real_part * initial_x)/(second_root_real_part - first_root_real_part);
    long double coefficient_a = initial_x - coefficient_b;
    std::string initial_equation = input_formatter->format_equation(a, b, c);
    long double max_amplitude_extremum_at_t = calculate_max_amplitude_extremum_at_t(first_root, second_root, coefficient_a, coefficient_b);
    return std::make_shared<calc::OverDampedSolution>(
        calc::OverDampedSolution{first_root, second_root, coefficient_a, coefficient_b, initial_equation, max_amplitude_extremum_at_t});
}

long double calc::OverDampedEquationSolver::calculate_max_amplitude_extremum_at_t(
        const calc::Solution::Root& first_root, const calc::Solution::Root& second_root, const long double& coefficient_a, const long double& coefficient_b) {
    long double ln_arg = (-coefficient_b * second_root.real_part) / (coefficient_a * first_root.real_part);
    return std::log(ln_arg) / (first_root.real_part - second_root.real_part);
}

std::shared_ptr<calc::Solution> calc::CriticallyDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double roots_real_part = -b/(2*a);
    calc::Solution::Root first_root{roots_real_part, 0};
    calc::Solution::Root second_root{roots_real_part, 0};
    long double coefficient_a = initial_x;
    long double coefficient_b = initial_x_prime - roots_real_part;
    std::string initial_equation = input_formatter->format_equation(a, b, c);
    long double max_amplitude_extremum_at_t = calculate_max_amplitude_extremum_at_t(first_root, coefficient_a, coefficient_b);
    return std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{first_root, second_root, coefficient_a, coefficient_b, initial_equation, max_amplitude_extremum_at_t});
}

long double calc::CriticallyDampedEquationSolver::calculate_max_amplitude_extremum_at_t(
        const calc::Solution::Root& first_root, const long double& coefficient_a, const long double& coefficient_b) {
    return -(coefficient_a * first_root.real_part + coefficient_b) / (coefficient_b * first_root.real_part);
}
