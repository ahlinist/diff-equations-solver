#ifndef EQUATION_SOLVER_HEADER
#define EQUATION_SOLVER_HEADER

#include <memory>

#include "solution.hpp"

namespace calc {
    class EquationSolver {
    public:
        virtual std::shared_ptr<calc::Solution> find_general_solution(const long double& discriminant, const double& a, const double& b, const double& c) = 0;
        virtual std::shared_ptr<calc::Solution> find_particular_solution(std::shared_ptr<calc::Solution> general_solution, const double& initial_x, const double& initial_x_prime) = 0;
    };

    class UnderDampedEquationSolver : public EquationSolver {
    public:
        std::shared_ptr<calc::Solution> find_general_solution(const long double& discriminant, const double& a, const double& b, const double& c) override;
        std::shared_ptr<calc::Solution> find_particular_solution(std::shared_ptr<calc::Solution> general_solution, const double& initial_x, const double& initial_x_prime) override;
    };
    
    class OverDampedEquationSolver : public EquationSolver {
    public:
        std::shared_ptr<calc::Solution> find_general_solution(const long double& discriminant, const double& a, const double& b, const double& c) override;
        std::shared_ptr<calc::Solution> find_particular_solution(std::shared_ptr<calc::Solution> general_solution, const double& initial_x, const double& initial_x_prime) override;
    };

    class CriticallyDampedEquationSolver : public EquationSolver {
    public:
        std::shared_ptr<calc::Solution> find_general_solution(const long double& discriminant, const double& a, const double& b, const double& c) override;
        std::shared_ptr<calc::Solution> find_particular_solution(std::shared_ptr<calc::Solution> general_solution, const double& initial_x, const double& initial_x_prime) override;
    };
}

#endif
