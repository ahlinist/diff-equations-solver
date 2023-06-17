#include "equation_solver.hpp"

#include <cmath>
#include <memory>

#include "solution.hpp"

std::shared_ptr<calc::Solution> calc::UnderDampedEquationSolver::find_general_solution(const long double& discriminant, const double& a, const double& b, const double& c) {
    long double roots_real_part = -b/(2*a);
    long double first_root_imaginary_part = std::sqrt(-discriminant)/(2*a);
    long double second_root_imaginary_part = -first_root_imaginary_part;
    return std::make_shared<calc::UnderDampedSolution>(calc::UnderDampedSolution{{roots_real_part, first_root_imaginary_part}, {roots_real_part, second_root_imaginary_part}});
}

std::shared_ptr<calc::Solution> calc::OverDampedEquationSolver::find_general_solution(const long double& discriminant, const double& a, const double& b, const double& c) {
    long double first_root_real_part = (-b - std::sqrt(discriminant))/(2*a);
    long double second_root_real_part = (-b + std::sqrt(discriminant))/(2*a);
    return std::make_shared<calc::OverDampedSolution>(calc::OverDampedSolution{{first_root_real_part, 0}, {second_root_real_part, 0}});
}

std::shared_ptr<calc::Solution> calc::CriticallyDampedEquationSolver::find_general_solution(const long double& discriminant, const double& a, const double& b, const double& c) {
    long double roots_real_part = -b/(2*a);
    return std::make_shared<calc::CriticallyDampedSolution>(calc::CriticallyDampedSolution{{roots_real_part, 0}, {roots_real_part, 0}});
}

void calc::UnderDampedEquationSolver::find_particular_solution(std::shared_ptr<calc::Solution> solution, const double& initial_x, const double& initial_x_prime) {    
    long double coefficient_a = initial_x;
    long double coefficient_b = (initial_x_prime - solution->get_first_root().real_part*initial_x)/solution->get_first_root().imaginary_part;
    solution->set_coefficient_a(coefficient_a);
    solution->set_coefficient_b(coefficient_b);
}

void calc::OverDampedEquationSolver::find_particular_solution(std::shared_ptr<calc::Solution> solution, const double& initial_x, const double& initial_x_prime) {
    long double coefficient_b = (initial_x_prime - solution->get_first_root().real_part*initial_x)/(solution->get_second_root().real_part - solution->get_first_root().real_part);
    long double coefficient_a = initial_x - coefficient_b;
    solution->set_coefficient_a(coefficient_a);
    solution->set_coefficient_b(coefficient_b);
}

void calc::CriticallyDampedEquationSolver::find_particular_solution(std::shared_ptr<calc::Solution> solution, const double& initial_x, const double& initial_x_prime) {
    long double coefficient_a = initial_x;
    long double coefficient_b = initial_x_prime - solution->get_first_root().real_part;
    solution->set_coefficient_a(coefficient_a);
    solution->set_coefficient_b(coefficient_b);
}
