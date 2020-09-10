// example:
// declaration of a muur object that contains four rectangle objects

#ifndef LINE_HPP
#define LINE_HPP

#include "hwlib.hpp"
#include "drawable.hpp"

class line : public drawable {
private:

   hwlib::xy end;
   
public:

   line( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end );
   void draw() override;

};

#endif // LINE_HPP