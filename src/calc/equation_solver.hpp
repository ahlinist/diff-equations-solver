#ifndef EQUATION_SOLVER_HEADER
#define EQUATION_SOLVER_HEADER

#include <memory>

#include "solution.hpp"

namespace calc {
    class EquationSolver {
    public:
        std::unique_ptr<calc::Solution> find_general_solution(double a, double b, double c);
    };
}

#endif
