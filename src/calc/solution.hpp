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
        explicit Solution(
            const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation);
        virtual ~Solution() {}
        virtual std::string get_result_equation() = 0;
        bool operator==(const Solution& other) const;
        Root get_first_root();
        Root get_second_root();
        long double get_coefficient_a();
        long double get_coefficient_b();
        virtual std::string get_initial_equation();
    protected:
        Root first_root{};
        Root second_root{};
        long double coefficient_a{};
        long double coefficient_b{};
        std::string initial_equation;
        virtual void validate_roots(const Root& first_root, const Root& second_root) = 0;
    };

    class UnderDampedSolution : public Solution {
    public:
        explicit UnderDampedSolution(
            const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation);
        std::string get_result_equation() override;
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };

    class OverDampedSolution : public Solution {
    public:
        explicit OverDampedSolution(
            const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation);
        std::string get_result_equation() override;
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };

    class CriticallyDampedSolution : public Solution {
    public:
        explicit CriticallyDampedSolution(
            const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b, const std::string& initial_equation);
        std::string get_result_equation() override;
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };
}

#endif
