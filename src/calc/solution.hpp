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
        virtual std::string display_general() = 0;
        virtual bool operator==(const Solution& other) const;
    protected:
        Root first_root;
        Root second_root;
        virtual void validate_roots(Root first_root, Root second_root) = 0;
    };

    class UnderDampedSolution : public Solution {
    public:
        explicit UnderDampedSolution(Root first_root, Root second_root);
        std::string display_general();
    protected:
        void validate_roots(Root first_root, Root second_root);
    };

    class OverDampedSolution : public Solution {
    public:
        explicit OverDampedSolution(Root first_root, Root second_root);
        std::string display_general();
    protected:
        void validate_roots(Root first_root, Root second_root);
    };

    class CriticallyDampedSolution : public Solution {
    public:
        explicit CriticallyDampedSolution(Root first_root, Root second_root);
        std::string display_general();
    protected:
        void validate_roots(Root first_root, Root second_root);
    };
}

#endif
