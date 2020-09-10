// example:
// declaration of a muur object that contains four rectangle objects

#ifndef BALL_HPP
#define BALL_HPP

#include "hwlib.hpp"
#include "drawable.hpp"
#include "line.hpp"
#include "circle.hpp"

class ball : public circle {
private:

   hwlib::xy speed;
   
public:

   ball( 
      hwlib::window & w, 
      const hwlib::xy & midpoint, 
      int radius, 
      const hwlib::xy & speed 
   );
   
   void update() override;
   void interact( drawable & other ) override; 
   
};

#endif // BALL_HPP