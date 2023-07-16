#include "equation_solver.hpp"

#include <cmath>
#include <memory>

#include "../text/equation_formatter.hpp"
#include "solution.hpp"

calc::EquationSolver::EquationSolver(const std::shared_ptr<text::EquationFormatter> equation_formatter) : equation_formatter{ equation_formatter } {}

std::shared_ptr<calc::Solution> calc::UnderDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double roots_real_part = -b/(2 * a);
    long double first_root_imaginary_part = std::sqrt(-discriminant)/(2 * a);
    calc::Solution::Root first_root{roots_real_part, first_root_imaginary_part};
    calc::Solution::Root second_root{roots_real_part, -first_root_imaginary_part};
    long double coefficient_a = initial_x;
    long double coefficient_b = (initial_x_prime - roots_real_part * initial_x) * first_root_imaginary_part;
    std::string initial_equation = equation_formatter->format_second_order(a, b, c);
    std::string result_equation = equation_formatter->format_under_damped_result(roots_real_part, first_root_imaginary_part, coefficient_a, coefficient_b);
    long double max_amplitude_extremum_at_t = calculate_max_amplitude_extremum_at_t(first_root, coefficient_a, coefficient_b);
    return std::make_shared<calc::UnderDampedSolution>(
        calc::UnderDampedSolution{first_root, second_root, coefficient_a, coefficient_b, initial_equation, result_equation, max_amplitude_extremum_at_t});
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
    std::string initial_equation = equation_formatter->format_second_order(a, b, c);
    std::string result_equation = equation_formatter->format_over_damped_result(first_root_real_part, second_root_real_part, coefficient_a, coefficient_b);
    long double max_amplitude_extremum_at_t = calculate_max_amplitude_extremum_at_t(first_root, second_root, coefficient_a, coefficient_b);
    return std::make_shared<calc::OverDampedSolution>(
        calc::OverDampedSolution{first_root, second_root, coefficient_a, coefficient_b, initial_equation, result_equation, max_amplitude_extremum_at_t});
}

long double calc::OverDampedEquationSolver::calculate_max_amplitude_extremum_at_t(
        const calc::Solution::Root& first_root, const calc::Solution::Root& second_root, const long double& coefficient_a, const long double& coefficient_b) {
    long double ln_arg = -(coefficient_a * first_root.real_part) / (coefficient_b * second_root.real_part);
    long double max_amplitude_extremum_at_t = 0;

    if (ln_arg > 0) {
        max_amplitude_extremum_at_t = std::log(ln_arg) / (second_root.real_part - first_root.real_part);
    }

    return max_amplitude_extremum_at_t >= 0 ? max_amplitude_extremum_at_t : 0;
}

std::shared_ptr<calc::Solution> calc::CriticallyDampedEquationSolver::solve(
        const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) {
    long double roots_real_part = -b/(2*a);
    calc::Solution::Root first_root{roots_real_part, 0};
    calc::Solution::Root second_root{roots_real_part, 0};
    long double coefficient_a = initial_x;
    long double coefficient_b = initial_x_prime - roots_real_part;
    std::string initial_equation = equation_formatter->format_second_order(a, b, c);
    std::string result_equation = equation_formatter->format_critically_damped_result(roots_real_part, coefficient_a, coefficient_b);
    long double max_amplitude_extremum_at_t = calculate_max_amplitude_extremum_at_t(first_root, coefficient_a, coefficient_b);
    return std::make_shared<calc::CriticallyDampedSolution>(
        calc::CriticallyDampedSolution{first_root, second_root, coefficient_a, coefficient_b, initial_equation, result_equation, max_amplitude_extremum_at_t});
}

long double calc::CriticallyDampedEquationSolver::calculate_max_amplitude_extremum_at_t(
        const calc::Solution::Root& first_root, const long double& coefficient_a, const long double& coefficient_b) {
    double long max_amplitude_extremum_at_t = -(coefficient_a * first_root.real_part + coefficient_b) / (coefficient_b * first_root.real_part);
    return max_amplitude_extremum_at_t >= 0 ? max_amplitude_extremum_at_t : 0;
}
