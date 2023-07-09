#include "solution_mapper.hpp"

#include <string>
#include <memory>
#include <map>
#include <stdexcept>

#include "../../libs/json.hpp"

#include "../calc/solution.hpp"

namespace mapper {
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Term, coefficient, type, argument)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Solution, multiplier, augend, addend)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Response, initialEquation, resultEquation, solution, max_at_t)
}

mapper::Response serialize_under_damped(std::shared_ptr<calc::Solution> solution_ptr) {
    mapper::Term multiplier{1, "e", solution_ptr->get_first_root().real_part};
    mapper::Term augend{solution_ptr->get_coefficient_a(), "cos", solution_ptr->get_first_root().imaginary_part};
    mapper::Term addend{solution_ptr->get_coefficient_b(), "sin", solution_ptr->get_first_root().imaginary_part};
    mapper::Solution solution{multiplier, augend, addend};
    mapper::Response response{solution_ptr->get_initial_equation(), solution_ptr->get_result_equation(), solution, solution_ptr->get_max_at_t()};
    return response;
}

mapper::Response serialize_over_damped(std::shared_ptr<calc::Solution> solution_ptr) {
    mapper::Term multiplier{1, "e", 0};
    mapper::Term augend{solution_ptr->get_coefficient_a(), "e", solution_ptr->get_first_root().real_part};
    mapper::Term addend{solution_ptr->get_coefficient_b(), "e", solution_ptr->get_second_root().real_part};
    mapper::Solution solution{multiplier, augend, addend};
    mapper::Response response{solution_ptr->get_initial_equation(), solution_ptr->get_result_equation(), solution, solution_ptr->get_max_at_t()};
    return response;
}

mapper::Response serialize_critically_damped(std::shared_ptr<calc::Solution> solution_ptr) {
    mapper::Term multiplier{1, "e", solution_ptr->get_first_root().real_part};
    mapper::Term augend{solution_ptr->get_coefficient_a(), "e", 0};
    mapper::Term addend{solution_ptr->get_coefficient_b(), "t", 1};
    mapper::Solution solution{multiplier, augend, addend};
    mapper::Response response{solution_ptr->get_initial_equation(), solution_ptr->get_result_equation(), solution, solution_ptr->get_max_at_t()};
    return response;
}

mapper::Response serialize_solution(std::shared_ptr<calc::Solution> solution) {
    if (std::dynamic_pointer_cast<calc::UnderDampedSolution>(solution)) {
        return serialize_under_damped(solution);
    } else if (std::dynamic_pointer_cast<calc::OverDampedSolution>(solution)) {
        return serialize_over_damped(solution);
    } else if (std::dynamic_pointer_cast<calc::CriticallyDampedSolution>(solution)) {
        return serialize_critically_damped(solution);
    } else {
        throw std::logic_error("Solution type not recognized");
    }
}

std::string mapper::SolutionMapperImpl::serialize(std::shared_ptr<calc::Solution> solution) {
    nlohmann::json jsonObj = serialize_solution(solution);
    return jsonObj.dump();
}
