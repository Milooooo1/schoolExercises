// example:
// declaration of a muur object that contains four rectangle objects

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "hwlib.hpp"
#include "drawable.hpp"
#include "line.hpp"

class circle : public drawable {
protected:

   int radius;
 
public:

   circle( hwlib::window & w, const hwlib::xy & midpoint, int radius );
   void draw() override;   

};

#endif // CIRCLE_HPP