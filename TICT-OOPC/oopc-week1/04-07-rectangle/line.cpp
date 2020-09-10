// example:
// definition of the functions of a line class 

#include "hwlib.hpp"
#include "line.hpp"

void line::print(){
   hwlib::line line( 
      hwlib::xy( start_x, start_y), 
      hwlib::xy( end_x, end_y ) );
   line.draw( w );
   w.flush();
}