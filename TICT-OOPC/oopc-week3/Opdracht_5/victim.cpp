#include "victim.hpp"

victim::victim( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size):
    rectangle(w, location, location + size),
    start( location ),
    end( location + size )
{}

void victim::draw() {
      rectangle::draw()
} 