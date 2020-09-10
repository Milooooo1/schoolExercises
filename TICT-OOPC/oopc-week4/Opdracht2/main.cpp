// ==========================================================================
//
// toggle a led on B.27
// by a switch on C.23
//
// This file is in the public domain.
//
// ==========================================================================

#include "hwlib.hpp"

int main( void ){	
   
   auto led0 = hwlib::target::pin_out( hwlib::target::pins::d7 );
   auto led1 = hwlib::target::pin_out( hwlib::target::pins::d6 );
   auto led2 = hwlib::target::pin_out( hwlib::target::pins::d5 );
   auto led3 = hwlib::target::pin_out( hwlib::target::pins::d4 );
   
   auto leds = hwlib::port_out_from( led0, led1, led2, led3 );
                                        //0123      _ = write ( 0 )     X = write ( 1 )
   for(;;){
    leds.write( 0 ); leds.flush();   
       
    led0.write( 1 ); leds.flush();      //X000
    led1.write( 1 ); leds.flush();      //0X00
    hwlib::wait_ms(400);                //XX00
    
    led2.write( 1 ); leds.flush();      //00X0
    led0.write( 0 ); leds.flush();      //_000
    hwlib::wait_ms(400);                //0XX0
    
    led3.write( 1 ); leds.flush();      //000X
    led1.write( 0 ); leds.flush();      //0_00
    hwlib::wait_ms(400);                //00XX
    
    led1.write( 1 ); leds.flush();      //0X00
    led3.write( 0 ); leds.flush();      //000_
    hwlib::wait_ms(400);                //0XX0
    
   }
}

         

