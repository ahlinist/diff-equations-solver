#pragma once

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
            const Root& first_root, 
            const Root& second_root, 
            const long double& coefficient_a, 
            const long double& coefficient_b, 
            const std::string& initial_equation,
            const std::string& result_equation,
            const long double& max_amplitude_extremum_at_t,
            const long double& decays_at_t);
        virtual ~Solution() {}
        bool operator==(const Solution& other) const;
        Root get_first_root() const;
        Root get_second_root() const;
        long double get_coefficient_a() const;
        long double get_coefficient_b() const;
        long double get_max_amplitude_extremum_at_t();
        std::string get_initial_equation();
        std::string get_result_equation();
        long double get_decays_at_t();
    protected:
        Root first_root{};
        Root second_root{};
        long double coefficient_a{};
        long double coefficient_b{};
        std::string initial_equation;
        std::string result_equation;
        long double max_amplitude_extremum_at_t;
        long double decays_at_t;
        virtual void validate_roots(const Root& first_root, const Root& second_root) = 0;
    };

    class UnderDampedSolution : public Solution {
    public:
        explicit UnderDampedSolution(
            const Root& first_root, 
            const Root& second_root, 
            const long double& coefficient_a, 
            const long double& coefficient_b, 
            const std::string& initial_equation,
            const std::string& result_equation,
            const long double& max_amplitude_extremum_at_t,
            const long double& decays_at_t);
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };

    class OverDampedSolution : public Solution {
    public:
        explicit OverDampedSolution(
            const Root& first_root, 
            const Root& second_root, 
            const long double& coefficient_a, 
            const long double& coefficient_b, 
            const std::string& initial_equation,
            const std::string& result_equation,
            const long double& max_amplitude_extremum_at_t,
            const long double& decays_at_t);
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };

    class CriticallyDampedSolution : public Solution {
    public:
        explicit CriticallyDampedSolution(
            const Root& first_root, 
            const Root& second_root, 
            const long double& coefficient_a, 
            const long double& coefficient_b, 
            const std::string& initial_equation,
            const std::string& result_equation,
            const long double& max_amplitude_extremum_at_t,
            const long double& decays_at_t);
    protected:
        void validate_roots(const Root& first_root, const Root& second_root) override;
    };
}
