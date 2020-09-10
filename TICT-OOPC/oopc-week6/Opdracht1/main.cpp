#include "hwlib.hpp"

int main( void ){	
   
   namespace target = hwlib::target;
   
   auto scl     = target::pin_oc( target::pins::scl );
   auto sda     = target::pin_oc( target::pins::sda );
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );  

   auto w1 = hwlib::part( 
      oled, 
      hwlib::xy( 0, 0 ),
      hwlib::xy( 128, 32));
   auto w2 = hwlib::part( 
      oled, 
      hwlib::xy( 0, 32 ),
      hwlib::xy( 128, 32));
      auto w3 = hwlib::part(
      oled,
      hwlib::xy(64, 0),
      hwlib::xy(64, 32));
   auto w4 = hwlib::part(
      oled,
      hwlib::xy(64, 32),
      hwlib::xy(128, 32));
      
   auto f1 = hwlib::font_default_8x8();
   auto d1 = hwlib::terminal_from( w1, f1 );  
   auto d2 = hwlib::terminal_from( w2, f1 );
   auto d3 = hwlib::terminal_from( w3, f1 );
   auto d4 = hwlib::terminal_from( w4, f1 );

   d1 << "\f"
      << "=======|\n"
      << " T_Left|\n"
      << "=======|\n" << hwlib::flush;  
   d2 << "\f"
      << "=======|\n"
      << " B_Left|\n"
      << "=======|\n" << hwlib::flush;  
   d3 << "\f"
      << "=======\n"
      << "T_Right\n"
      << "=======\n" << hwlib::flush;     
   d4 << "\f"
      << "=======\n"
      << "B_Right\n"
      << "=======\n" << hwlib::flush;  
}
