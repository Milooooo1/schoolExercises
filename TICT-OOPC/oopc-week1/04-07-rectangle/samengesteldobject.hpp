
#ifndef SAMENGESTELDOBJECT_HPP
#define SAMENGESTELDOBJECT_HPP

#include "rectangle.hpp"
#include "hwlib-all.hpp"
#include "line.hpp"

class car {
private:
   hwlib::window & w;
   rectangle body;
   line windshield;
   int length, width, start_x, start_y;
   hwlib::circle wheel1, wheel2;
public:
   car(hwlib::window & w, int length, int width, int start_x, int start_y);
   void print();
};


#endif // SAMENGESTELDOBJECT_HPP
