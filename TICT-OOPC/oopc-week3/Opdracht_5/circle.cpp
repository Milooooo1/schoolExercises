#include "circle.hpp"

circle::circle( hwlib::window & w, const hwlib::xy & midpoint, int radius ):
    drawable( w, midpoint - hwlib::xy( radius, radius ), 
    hwlib::xy( radius, radius ) * 2 ),
    radius( radius )
{}
   
void circle::draw() {
    hwlib::circle c( location + hwlib::xy( radius, radius ), radius );
    c.draw( w );
}