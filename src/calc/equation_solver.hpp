#ifndef EQUATION_SOLVER_HEADER
#define EQUATION_SOLVER_HEADER

#include <memory>

#include "../input/input_formatter.hpp"
#include "solution.hpp"

namespace calc {
    class EquationSolver {
    protected:
        std::shared_ptr<input::InputFormatter> input_formatter;
    public:
        EquationSolver() {}
        explicit EquationSolver(const std::shared_ptr<input::InputFormatter> input_formatter);
        virtual ~EquationSolver() {}
        virtual std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) = 0;
    };

    class UnderDampedEquationSolver : public EquationSolver {
    public:
        using EquationSolver::EquationSolver;
        std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };
    
    class OverDampedEquationSolver : public EquationSolver {
    public:
        using EquationSolver::EquationSolver;
        std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };

    class CriticallyDampedEquationSolver : public EquationSolver {
    public:
        using EquationSolver::EquationSolver;
        std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };
}

#endif
