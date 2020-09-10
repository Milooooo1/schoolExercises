// example:
// definition of the functions of a muur object

#include "muur.hpp"

muur::muur( hwlib::window & w, const hwlib::xy & start, const hwlib::xy & end, int update_interval, const std::vector<int> & bounce ):
   rectangle(w, start, end),
   update_interval( update_interval ),
   bounce ( bounce ),
   fillTop( w, hwlib::xy( 1, 1 )  , hwlib::xy( 126, 2  )),     
   fillBottom( w, hwlib::xy( 1, 62 ) , hwlib::xy( 126, 2 )),  
   fillRight( w, hwlib::xy( 126, 1 ), hwlib::xy( 2, 62 )),
   fillLeft( w, hwlib::xy( 1, 1 )  , hwlib::xy( 2, 62   ))     
{}

void muur::draw() {
   rectangle::draw();
   if(filled){
      fillTop.draw();
      fillRight.draw();
      fillBottom.draw();
      fillLeft.draw();
   }
}

void muur::update(){
   if(update_count >= update_interval){
      filled = !filled;
      update_count = 0;
   }else{
      update_count++;
   }
}
