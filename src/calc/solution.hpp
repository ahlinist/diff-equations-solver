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
        Solution() {}
        explicit Solution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b);
        virtual ~Solution() {}
        virtual std::string display_general() = 0;
        virtual std::string display_particular() = 0;
        bool operator==(const Solution& other) const;
        Root get_first_root();
        Root get_second_root();
        long double get_coefficient_a();
        long double get_coefficient_b();
    protected:
        Root first_root{};
        Root second_root{};
        long double coefficient_a{};
        long double coefficient_b{};
        virtual void validate_roots(Root first_root, Root second_root) = 0;
    };

    class UnderDampedSolution : public Solution {
    public:
        explicit UnderDampedSolution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b);
        std::string display_general() override;
        std::string display_particular() override;
    protected:
        void validate_roots(Root first_root, Root second_root);
    };

    class OverDampedSolution : public Solution {
    public:
        explicit OverDampedSolution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b);
        std::string display_general() override;
        std::string display_particular() override;
    protected:
        void validate_roots(Root first_root, Root second_root);
    };

    class CriticallyDampedSolution : public Solution {
    public:
        explicit CriticallyDampedSolution(Root first_root, Root second_root, long double coefficient_a, long double coefficient_b);
        std::string display_general() override;
        std::string display_particular() override;
    protected:
        void validate_roots(Root first_root, Root second_root);
    };
}

#endif
