#include "line.hpp"

line::line( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end ):
      drawable( w, location, end - location ),
      end( end )
{}

void line::draw() {
      hwlib::line x( location, end );
      x.draw( w );;
}