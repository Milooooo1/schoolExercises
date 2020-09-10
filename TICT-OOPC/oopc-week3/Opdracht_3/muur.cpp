// example:
// definition of the functions of a muur object

#include "muur.hpp"

muur::muur( hwlib::window & w, const hwlib::xy & start, const hwlib::xy & end, int update_interval ):
   rectangle(start, end, hwlib::color(255, 255, 255)),
   update_interval( update_interval )
   fill( w, start + hwlib::xy( 1, 1 )  , end - hwlib::xy( 1, 1  ))   

   //Oude code voor het geval ik moet testen
   /*
   fillTop( w, hwlib::xy( 1, 1 )  , hwlib::xy( 126, 2  )),     
   fillBottom( w, hwlib::xy( 1, 62 ) , hwlib::xy( 126, 2 )),  
   fillRight( w, hwlib::xy( 126, 1 ), hwlib::xy( 2, 62 )),
   fillLeft( w, hwlib::xy( 1, 1 )  , hwlib::xy( 2, 62   )) 
   */
{}

void muur::draw( hwlib::window & w ){
   rectangle::draw(w);
   if(filled){
      fill.draw();
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