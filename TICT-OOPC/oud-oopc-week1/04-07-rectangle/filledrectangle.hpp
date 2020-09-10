// example:
// declaration of a rectangle object that is contains four line objects

#ifndef FILLEDRECTANGLE_HPP
#define FILLEDRECTANGLE_HPP

#include "line.hpp"

class filledrectangle {
private:
   hwlib::window & w;
   line left, right, top, bottom;
   int start_x, start_y, end_x, end_y;
public:
   filledrectangle( hwlib::window & w, int start_x, int start_y, int end_x, int end_y);
   void print();
};


#endif // FILLEDRECTANGLE_HPP
