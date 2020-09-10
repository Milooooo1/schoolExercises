#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "adt.hpp"
#include <ostream>

TEST_CASE("vector += vector"){
    vector x(1, 2);
    x += vector(2, 3);
    REQUIRE( x == vector( 3, 5));
}

TEST_CASE("vector + vector"){
    vector a(2, 6), b(3, 1);
    vector c = a + b;
    REQUIRE( c == vector(5, 7));
}

TEST_CASE("vector * vector"){
    vector a(2, 3), b(2, 3);
    vector c = a * b;
    REQUIRE( c == vector(4, 9));
}

TEST_CASE("vector *= vector"){
    vector a(4, 2), b(2, 3);
    b *= a;
    REQUIRE( b == vector(8, 6));
}

TEST_CASE("output vector"){
    vector a(42, 22);
    std::stringstream s;
    s << a;
    REQUIRE( s.str() == "0x2a , 0x16" );
}

//Dit zijn de test cases van Sua Wilhelm

TEST_CASE( "vector equal" ){
   vector v(1, 2);
   REQUIRE( v == vector(1, 2) );
}

TEST_CASE( "vector plus" ){
   vector v(2, 3);
   vector x = v + vector (2,3);
   REQUIRE( x == vector(4, 6) );
}

TEST_CASE( "vector plus vector" ){
   vector v(2, 3);
   vector x = v + (v + vector (2,3));
   REQUIRE( x == vector(6, 9) );
}

TEST_CASE("vector by reference" ){
   vector v(2, 3);
   v += vector (2,3);
   REQUIRE( v == vector(4, 6) );
}

TEST_CASE( "vector reference times int" ){
   vector v(6, 12);
   vector x(3, 3);
   v*=x;
   REQUIRE( v == vector(18, 36) );
}


//
// Alle test cases van Sua slaagden in een keer! Er waren 
// geen aanpassingen meer nodig.
//