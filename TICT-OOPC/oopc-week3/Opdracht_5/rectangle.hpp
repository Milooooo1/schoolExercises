// example:
// declaration of a muur object that contains four rectangle objects

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "hwlib.hpp"
#include "drawable.hpp"
#include "line.hpp"

class rectangle : public drawable {
private:
 
   hwlib::xy start, end;
   hwlib::color ink;

 
public:
   rectangle( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size);
   virtual void draw() override;  

};

#endif // RECTANGLE_HPP