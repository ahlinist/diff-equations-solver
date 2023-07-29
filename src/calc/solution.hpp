#pragma once

namespace calc {
    class Solution {
    public:
        struct Root {
            long double real_part{};
            long double imaginary_part{};
        };
        Solution() {}
        explicit Solution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b);
        virtual ~Solution() {}
        bool operator==(const Solution& other) const;
        Root get_first_root() const;
        Root get_second_root() const;
        long double get_coefficient_a() const;
        long double get_coefficient_b() const;
    protected:
        Root first_root{};
        Root second_root{};
        long double coefficient_a{};
        long double coefficient_b{};
        virtual void validate_roots(const Root& first_root, const Root& second_root) = 0;
    };

    class UnderDampedSolution : public Solution {
    public:
        explicit UnderDampedSolution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b);
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };

    class OverDampedSolution : public Solution {
    public:
        explicit OverDampedSolution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b);
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };

    class CriticallyDampedSolution : public Solution {
    public:
        explicit CriticallyDampedSolution(const Root& first_root, const Root& second_root, const long double& coefficient_a, const long double& coefficient_b);
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };
}
