// example:
// declaration of a muur object that contains four rectangle objects

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "hwlib.hpp"
#include <vector>

class drawable {
protected:

   hwlib::window & w;
   hwlib::xy location;
   hwlib::xy size;
   std::vector<int> bounce;
   
public:

   drawable( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size, const std::vector<int> & bounce = {1,1});   
   virtual void draw() = 0;
   virtual void update(){}
   bool overlaps( const drawable & other );   
   virtual void interact( drawable & other ){}
   hwlib::ostream & print( hwlib::ostream & out );
   int return_x();
   int return_y();     
};

#endif // DRAWABLE_HPP