#include <hwlib.hpp>
#include "muur.hpp"
#include <array>

// ===========================================================================

class drawable {
protected:

   hwlib::window & w;
   hwlib::xy location;
   hwlib::xy size;
   
public:

   drawable( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size ):
      w( w ),
      location( location ),
      size( size )
   {}      
   
   virtual void draw() = 0;
   virtual void update(){}
   bool overlaps( const drawable & other );   
   virtual void interact( drawable & other ){}
   
   hwlib::ostream & print( hwlib::ostream & out ) const {
      return out << location << " " << ( location + size );
   }      
};

hwlib::ostream & operator<<( hwlib::ostream & lhs, const drawable & rhs ){
   return rhs.print( lhs );
}

bool within( int x, int a, int b ){
   return ( x >= a ) && ( x <= b );
}

bool drawable::overlaps( const drawable & other ){
   
   bool x_overlap = within( 
      location.x, 
      other.location.x, 
      other.location.x + other.size.x
   ) || within( 
      other.location.x, 
      location.x, 
      location.x + size.x
   );
     
   bool y_overlap = within( 
      location.y, 
      other.location.y, 
      other.location.y + other.size.y
   ) || within( 
      other.location.y, 
      location.y, 
      location.y + size.y
   );
   
   return x_overlap && y_overlap;
}

// ===========================================================================

class line : public drawable {
private:

   hwlib::xy end;
   
public:

   line( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end ):
      drawable( w, location, end - location ),
      end( end )
   {}
   
   void draw() override {
      hwlib::line x( location, end );
      x.draw( w );;
   }
};

// ===========================================================================

class circle : public drawable {
protected:

   int radius;
 
public:

   circle( hwlib::window & w, const hwlib::xy & midpoint, int radius ):
      drawable( w, 
         midpoint - hwlib::xy( radius, radius ), 
         hwlib::xy( radius, radius ) * 2 ),
      radius( radius )
   {}
   
   void draw() override {
      hwlib::circle c( location + hwlib::xy( radius, radius ), radius );
      c.draw( w );
   }
};

// ===========================================================================

class ball : public circle {
private:

   hwlib::xy speed;
   
public:

   ball( 
      hwlib::window & w, 
      const hwlib::xy & midpoint, 
      int radius, 
      const hwlib::xy & speed 
   ):
      circle( w, midpoint, radius ),
      speed( speed )  
   {}
   
   void update() override {
      location = location + speed; 
   }
   
   void interact( drawable & other ) override {
      if( this != & other){
         if( overlaps( other )){
            speed.x *= -1;
            speed.y *= -1;
         }
      }
   }   
};

// ===========================================================================

int main(){
   hwlib::target::window w( hwlib::xy( 128, 64 ), hwlib::white, hwlib::black, 2 );
   //line top( w, hwlib::xy(   3,  3 ), hwlib::xy( 124,  3 ) );
   //line right( w, hwlib::xy( 124,  4 ), hwlib::xy( 124, 60 ) );
   //line bottom( w, hwlib::xy(   4, 60 ), hwlib::xy( 124, 60 ) );
   //line left( w, hwlib::xy(   3,  3 ), hwlib::xy(   3, 60 )  );
   ball b( w, hwlib::xy( 50, 20 ), 9, hwlib::xy( 5, 2 ) );
   muur mTop( w, hwlib::xy( 0, 0 ), hwlib::xy( 127, 3 ), 10);
   muur mBottom( w, hwlib::xy( 0, 60 ), hwlib::xy( 127, 63 ), 10);
   muur mLeft( w, hwlib::xy( 0, 0 ), hwlib::xy( 3, 63 ), 10);
   muur mRight( w, hwlib::xy( 124, 0 ), hwlib::xy( 127, 63 ), 10);

   
   std::array< drawable *, 5 > objects = { &b, &top, &left, &right, &bottom };
   std::array< muur *, 4 > wallSegments = { &mTop, &mBottom, &mLeft, &mRight };

   for(;;){
      w.clear();
      for( auto & p : objects ){
         p->draw();
      }
      for( auto & p : wallSegments){
         p->draw(w);
      }

      w.flush();
      hwlib::wait_ms( 200 );
      for( auto & p : objects ){
         p->update();
      }
      for( auto & p : wallSegments){
         p->update();
      }

      for( auto & p : objects ){
         for( auto & other : objects ){
            p->interact( *other );
         } 
      }
   }
}

