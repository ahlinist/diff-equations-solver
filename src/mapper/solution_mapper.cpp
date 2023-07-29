#include "solution_mapper.hpp"

#include <string>
#include <vector>
#include <map>

#include "../../libs/json.hpp"

#include "../calc/solution.hpp"
#include "../model/domain_model.hpp"

namespace mapper {
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SecondOrderSolutionDto, initialEquation, resultEquation, functionDataPoints)
}

//TODO: to drop a separate DTO struct, serialize std objects
mapper::SecondOrderSolutionDto serialize_solution(model::SolvedSecondOrderEquation solved_equation) {
    std::vector<std::map<std::string, long double>> data{};

    for (const model::FunctionDataPoint& data_point : solved_equation.function_data_points) {
        std::map<std::string, long double> data_map{};
        data_map["t"] = data_point.time;
        data_map["y"] = data_point.value;
        data.push_back(data_map);
    }

    mapper::SecondOrderSolutionDto response{ solved_equation.initial_equation, solved_equation.solution_equation, data};
    return response;
}

std::string mapper::SolutionMapperImpl::serialize(model::SolvedSecondOrderEquation solved_equation) {
    nlohmann::json jsonObj = serialize_solution(solved_equation);
    return jsonObj.dump();
}
