#pragma once
#include "project_headers.hpp"
#include <array>
namespace data {

    constexpr std::size_t fuel_outer_size = 8;
    extern std::array<glm::vec2, fuel_outer_size> fuel_tank_outer;
}