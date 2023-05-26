#ifndef EQUATION_SOLVER_HEADER
#define EQUATION_SOLVER_HEADER

#include "solution.hpp"

namespace calc {
    class EquationSolver {
    public:
        calc::Solution* find_general_solution(double a, double b, double c);
    };
}

#endif
