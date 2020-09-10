#include "rectangle.hpp"

rectangle::rectangle( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size):
    drawable(w, location, size),
    start( location ),
    end( location + size )
{}

void rectangle::draw() {
      line(w, hwlib::xy( start.x, start.y ), hwlib::xy( start.x,   end.y + 1 ) ).draw();
      line(w, hwlib::xy( end.x,   start.y ), hwlib::xy( end.x,     end.y + 1 ) ).draw();
      line(w, hwlib::xy( start.x, start.y ), hwlib::xy( end.x + 1, start.y   ) ).draw();
      line(w, hwlib::xy( start.x, end.y   ), hwlib::xy( end.x + 1, end.y     ) ).draw();
} 