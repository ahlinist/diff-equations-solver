#ifndef SOLUTION_HEADER
#define SOLUTION_HEADER

#include <string>

namespace calc {
    class Solution {
    public:
        struct Root {
            long double real_part{};
            long double imaginary_part{};
        };
        explicit Solution(Root first_root, Root second_root) 
            : first_root{ first_root }, second_root{ second_root } 
            {}
        virtual ~Solution() {}
        virtual std::string display() = 0;
    protected:
        Root first_root;
        Root second_root;
    };

    class UnderDampedSolution : public Solution {
        using Solution::Solution;
    public:
        std::string display();
    };

    class OverDampedSolution : public Solution {
        using Solution::Solution;
    public:
        std::string display();
    };

    class CriticallyDampedSolution : public Solution {
        using Solution::Solution;
    public:
        std::string display();
    };
}

#endif
