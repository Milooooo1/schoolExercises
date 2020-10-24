#include "hwlib.hpp"

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void application();
extern "C" void print_asciz(const char *s);

int main(void){

   hwlib::wait_ms(2000);
   application();
   
}