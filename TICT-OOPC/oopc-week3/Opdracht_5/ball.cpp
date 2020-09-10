#include "ball.hpp"
#include "hwlib.hpp"
#include "muur.hpp"
#include "drawable.hpp"
#include <ostream>

ball::ball(hwlib::window & w, const hwlib::xy & midpoint, int radius, const hwlib::xy & speed):
      circle( w, midpoint, radius ),
      speed( speed )  
{}

void ball::update() {
    location = location + speed; 
}

void ball::interact( drawable & other ) {
    if( this != & other){
        if( overlaps( other )){
            speed.x *= other.return_x();
            speed.y *= other.return_y();
            // std::cout   << "Direction changed" << std::endl 
            //             << "speedX: " << speed.x << " it has been multiplied by: " << other.return_x() << std::endl 
            //             << "speedY: " << speed.y << " it has been multiplied by: " << other.return_y()<< std::endl;
        }
    }
}  