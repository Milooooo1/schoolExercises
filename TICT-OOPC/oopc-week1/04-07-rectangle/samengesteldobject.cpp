#include "rectangle.hpp"
#include "line.hpp"
#include "samengesteldobject.hpp"

car::car(hwlib::window & w, int length, int width, int start_x, int start_y):
   w( w ),
   body( w, start_x, start_y, start_x + length, start_y + width),
   windshield( w, start_x + 10, start_y, start_x + 20, start_y - 10),
   wheel1(hwlib::xy(start_x + 10, start_y + width), 8, hwlib::color(1,1,1)),
   wheel2(hwlib::xy(start_x + length - 10, start_y + width), 8, hwlib::color(1,1,1))   
{}

void car::print(){
    body.print();
    windshield.print();
    wheel1.draw(w);
    wheel2.draw(w);
    w.flush();
}

