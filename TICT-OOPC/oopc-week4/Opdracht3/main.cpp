#include "hwlib.hpp"
#include <cmath>

void more_less_patern( hwlib::port_out & leds, hwlib::target::pin_in & sw1, hwlib::target::pin_in & sw2){
   int counter = 0;
   for(;;){
      sw2.refresh();
      hwlib::wait_ms(80);
      if(sw2.read() == 0){
         if(counter < 4){
            counter++;                                              
         }    
         leds.write( uint8_t(pow(2, counter ))); leds.flush();                                                                                                              
      }
      sw1.refresh();
      hwlib::wait_ms(80); 
      if(sw1.read() == 0){
         if(counter >= 0){
            counter--;
         }
         leds.write( uint8_t(pow(2, counter ))); leds.flush();       
      }
   }
}

int main( void ){	  
   hwlib::wait_ms(10);
   auto led0 = hwlib::target::pin_out( hwlib::target::pins::d7 );
   auto led1 = hwlib::target::pin_out( hwlib::target::pins::d6 );
   auto led2 = hwlib::target::pin_out( hwlib::target::pins::d5 );
   auto led3 = hwlib::target::pin_out( hwlib::target::pins::d4 );
   auto sw1  = hwlib::target::pin_in( hwlib::target::pins::d3 );
   auto sw2  = hwlib::target::pin_in( hwlib::target::pins::d8 );
   
   auto leds = hwlib::port_out_from( led0, led1, led2, led3 );

   sw1.pullup_enable();
   sw2.pullup_enable();

   // for(;;){
   //    sw1.refresh();
   //    sw2.refresh();
   //    hwlib::cout << "sw1: "<< (bool)sw1.read() << "\t| sw2: "<< (bool)sw2.read() << hwlib::endl;
   // }

   ::more_less_patern( leds, sw1, sw2 );

}