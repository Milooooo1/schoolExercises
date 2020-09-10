// example:
// declaration of a muur object that contains four rectangle objects

#ifndef MUUR_HPP
#define MUUR_HPP

#include "hwlib.hpp"

class muur : public hwlib::rectangle {
private:
   bool filled = true;
   int update_interval, update_count;
   hwlib::xy start, end;
   hwlib::rectangle fill; //Top, fillBottom, fillRight, fillLeft;

public:
   muur( hwlib::window & w, const hwlib::xy & start, const hwlib::xy & end, int update_interval);
   void draw(hwlib::window & w);
   void update();
};


#endif // MUUR_HPP