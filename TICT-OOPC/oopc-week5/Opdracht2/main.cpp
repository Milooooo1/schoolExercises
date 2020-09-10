#include "hwlib.hpp"

int main( void ){	   
   namespace target = hwlib::target;
   
   auto ds   = target::pin_out( target::pins::d9 );
   auto shcp = target::pin_out( target::pins::d7 );
   auto stcp = target::pin_out( target::pins::d8 );
   auto led1 = target::pin_out( target::pins::d2 );
   auto led2 = target::pin_out( target::pins::d3 );
   auto led3 = target::pin_out( target::pins::d4 );
   auto led4 = target::pin_out( target::pins::d5 );
   auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso( 
      shcp, 
      ds, 
      hwlib::pin_in_dummy 
   );
   auto hc595 = hwlib::hc595( spi, stcp );
   
   auto leds = hwlib::port_out_from( 
      hc595.p4,
      hc595.p5,
      hc595.p6,
      hc595.p7,
      led1,
      led2,
      led3,
      led4
   );
   
   hwlib::kitt( leds );
}
