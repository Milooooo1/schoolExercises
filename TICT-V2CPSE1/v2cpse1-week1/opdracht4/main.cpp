#include "hwlib.hpp"

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void print_asciz(const char *s);
extern "C" void application();
extern char *wrd;

// void print_asciz( const char * s ){
//    while( *s != '\0'){
//       uart_put_char( *s );
//       ++s;
//    }
// }

// void application(){
//    print_asciz( "Hello world, the ANSWER is 42! @[]`{}~\n" );	
// }

extern "C" char toggle_case( char c ){
   if(c >= 65 && c <= 90){ //check hoofdletter
      c = c + 32;
   } else if (c >= 97 && c <= 122){ //check kleineletter
      c = c - 32;
   }
   return c;
}

int main( void ){	
   
   namespace target = hwlib::target;   
    
   // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application();
}