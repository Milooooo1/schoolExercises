#include <hwlib.hpp>
#include "muur.hpp"
#include "drawable.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "ball.hpp"
#include "rectangle.hpp"
#include "victim.hpp"
#include <ostream>
#include <array>

// ===========================================================================

int main(){
   hwlib::target::window w( hwlib::xy( 128, 64 ), hwlib::white, hwlib::black, 2 );
   ball b( w, hwlib::xy( 64, 32 ), 9, hwlib::xy( 5, 2 ) );
   muur mTop( w, hwlib::xy( 0, 0 ), hwlib::xy( 127, 2 ), 20, {-1,1});
   muur mBottom( w, hwlib::xy( 0, 61 ), hwlib::xy( 127, 2 ), 20, {1,-1});
   muur mLeft( w, hwlib::xy( 0, 0 ), hwlib::xy( 2, 63 ), 20, {1,1});
   muur mRight( w, hwlib::xy( 125, 0 ), hwlib::xy( 2, 63 ), 20, {-1,-1});
   victim victim( w, hwlib::xy( 80, 40), hwlib::xy(10,10));
   
   std::array< drawable *, 5 > objects = { &b, &mTop, &mBottom, &mLeft, &mRight };
   std::array< drawable *, 2 > victimArray = {&b, &victim};

   for(;;){
      w.clear();
      for( auto & p : objects ){
         p->draw();
      }

      victim.draw();
      w.flush();
      hwlib::wait_ms( 200 );
      for( auto & p : objects ){
         p->update();
      }

      for( auto & p : objects ){
         for( auto & other : objects ){
            p->interact( *other );
         } 
      }
      
      for( auto & p : victimArray ){
         if( p != & victim){
            if( p->overlaps( victim )){
               std::cout << "Victim touched." << std::endl 
                         << " Original start position: " << victim.start << std::endl 
                         << "Original end position: " << victim.end << std::endl;
               victim.start - hwlib::xy(1,1);
               victim.end - hwlib::xy(1,1);
               std::cout << "Shrinked start position: " << victim.start << std::endl 
                         << "Shrinked end position: " << victim.end << std::endl;
               w.flush();          
            }
         }
      }
   
   }
}

