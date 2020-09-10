// example:
// declaration of a muur object that contains four rectangle objects

#ifndef MUUR_HPP
#define MUUR_HPP

#include "hwlib.hpp"
#include "drawable.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include <vector>

class muur : public rectangle {
private:
   bool filled = true;
   int update_interval, update_count;
   hwlib::xy start, end;
   rectangle fillTop, fillBottom, fillRight, fillLeft;

public:
   muur( hwlib::window & w, const hwlib::xy & start, const hwlib::xy & end, int update_interval, const std::vector<int> & bounce );
   void draw() override ;
   void update();
};

#endif // MUUR_HPP