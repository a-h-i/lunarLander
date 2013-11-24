#include "ui.hpp"
#include <cmath>

ui::FuelControl::FuelControl(float delta) : fuel(), delta_(delta) {
    if(!std::signbit(delta)) {
        throw std::invalid_argument("FuelControl constructed with positive delta");
    }
}