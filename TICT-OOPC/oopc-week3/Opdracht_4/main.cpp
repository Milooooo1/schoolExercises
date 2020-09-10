#include <hwlib.hpp>
#include "muur.hpp"
#include "drawable.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "ball.hpp"
#include "rectangle.hpp"
#include <array>

// ===========================================================================

int main(){
   hwlib::target::window w( hwlib::xy( 128, 64 ), hwlib::white, hwlib::black, 2 );
   ball b( w, hwlib::xy( 64, 32 ), 9, hwlib::xy( 5, 2 ) );
   muur mTop( w, hwlib::xy( 0, 0 ), hwlib::xy( 127, 2 ), 20, {-1,1});
   muur mBottom( w, hwlib::xy( 0, 61 ), hwlib::xy( 127, 2 ), 20, {1,-1});
   muur mLeft( w, hwlib::xy( 0, 0 ), hwlib::xy( 2, 63 ), 20, {1,1});
   muur mRight( w, hwlib::xy( 125, 0 ), hwlib::xy( 2, 63 ), 20, {-1,-1});

   
   std::array< drawable *, 5 > objects = { &b, &mTop, &mBottom, &mLeft, &mRight };
   for(;;){
      w.clear();
      for( auto & p : objects ){
         p->draw();
      }

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
   }
}

