#include "andDecorator.hpp"
#include "hwlib.hpp"

int main(){

    auto pin1 = hwlib::target::pin_in( hwlib::target::d6 );
    auto pin2 = hwlib::target::pin_in( hwlib::target::d7 );
    auto pin3 = hwlib::target::pin_in( hwlib::target::d8 );

    pin3.set( and_pin_ins(pin1, pin2) );    

    return 1;
}