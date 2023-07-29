#pragma once

#include <memory>

#include "solution.hpp"

namespace calc {
    class EquationSolver {
    public:
        virtual ~EquationSolver() {}
        virtual std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) = 0;
    };

    class UnderDampedEquationSolver : public EquationSolver {
    public:
        virtual std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };
    
    class OverDampedEquationSolver : public EquationSolver {
    public:
        virtual std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };

    class CriticallyDampedEquationSolver : public EquationSolver {
    public:
        virtual std::shared_ptr<calc::Solution> solve(
            const long double& discriminant, const double& a, const double& b, const double& c, const double& initial_x, const double& initial_x_prime) override;
    };
}
