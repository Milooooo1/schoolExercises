// example:
// declaration of a muur object that contains four rectangle objects

#ifndef VICTIM_HPP
#define VICTIM_HPP

#include "hwlib.hpp"
#include "drawable.hpp"
#include "line.hpp"

class victim : public rectangle {
private:
 
   hwlib::color ink;

public:
    hwlib::xy start, end;
    victim( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size);
    virtual void draw() override;  

};

#endif // VICTIM_HPP