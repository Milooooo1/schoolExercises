// example:
// definition of the functions of a rectangle object

#include "rectangle.hpp"
#include "line.hpp"
#include "filledrectangle.hpp"
#include "hwlib.hpp"
#include <iostream>

filledrectangle::filledrectangle( hwlib::window & w, int start_x, int start_y, int end_x, int end_y):
   w( w ),
   left(   w, start_x, start_y, start_x,   end_y + 1 ),
   right(  w, end_x,   start_y, end_x,     end_y + 1 ),
   top(    w, start_x, start_y, end_x + 1, start_y ),
   bottom( w, start_x, end_y,   end_x + 1, end_y ),
   start_x(start_x),
   start_y(start_y),
   end_x(end_x),
   end_y(end_y)
{}

void filledrectangle::print(){
    left.print();
    right.print();
    top.print();
    bottom.print();
    for(int i = start_y; i < end_y+1; i++){
        for(int j = start_x; j < end_x+1; j++){
            w.write(hwlib::xy( i, j), hwlib::color(1,1,1));
        }
    }
    w.flush();

}

