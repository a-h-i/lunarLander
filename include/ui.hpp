#pragma once
#include "utility.hpp"
#include <memory>
#include <stdexcept>
namespace ui {


namespace components {    
struct Fuel {
    float status;
    Fuel(): status(1.0f) {}
};



}// namespace ui::components


/**
 *@brief Each call to update level calculates fuel level and returns new value clamped [0,1].
 *
 */
class FuelControl{
    components::Fuel fuel;
    float delta_;
public:
    /**
     *@param delta fuel level change per call to updateLevel.
     *@exception std::invalid_argument if delta is not negative.
     */
    FuelControl(float delta);
    inline float updateLevel() {
        fuel.status = utility::math::clamp(fuel.status + delta_, 1.0f, 0.0f);
        return fuel.status;
    }
    inline float status() {
        return fuel.status;
    }
};


class FuelView {
    FuelControl fc;
    struct FViewImpl;
    FViewImpl * impl;
public:
    /**
     * @exception ShaderError if an error occured while creating shaders.
     */
    FuelView(FuelControl &fc);
    void changeController(FuelControl &other) {fc = other;}
    void draw();
    ~FuelView();

};

}// namespace ui