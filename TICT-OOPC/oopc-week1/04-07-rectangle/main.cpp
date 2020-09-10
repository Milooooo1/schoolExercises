#include "hwlib.hpp"
#include "rectangle.hpp"
#include "filledrectangle.hpp"
#include "samengesteldobject.hpp"
//#include "hwlib-graphics-drawables.hpp"

int main(int argc, char **argv){
    
   // the window in which we want to print the line
   hwlib::target::window w( hwlib::xy( 128, 128 ));    
   
   //rectangle square( w, 20, 20, 40, 40 );
   //square.print();
   //filledrectangle fill(w, 20, 20, 40, 40);
   //fill.print();
   
   car auto1(w, 60, 15, 30, 20);
   auto1.print();

   car auto2(w, 80, 20, 30, 90);
   auto2.print();
 
   
   // keep the window around until we close it
   for(;;){ w.poll(); }       
}
