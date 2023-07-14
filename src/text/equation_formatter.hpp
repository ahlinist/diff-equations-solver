#pragma once

#include <string>

namespace text {
    class EquationFormatter {
    public:
        virtual ~EquationFormatter() {}
        virtual std::string format_second_order(const double& a, const double& b, const double& c) = 0;
    };

    class SecondOrderEquationFormatter : public EquationFormatter {
    public:
        std::string format_second_order(const double& a, const double& b, const double& c) override;
    };
}
