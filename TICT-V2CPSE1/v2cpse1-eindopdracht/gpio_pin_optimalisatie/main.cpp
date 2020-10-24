#include "hwlib.hpp"
//#include "../../hwlib/attic/chris/due-spi.hpp"

namespace target = hwlib::target;

int main( void ){
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 2'000 );
   hwlib::cout << "ST7789 demo\n" << hwlib::flush;   
   
   auto _sclk = hwlib::target::pin_out{ hwlib::target::pins::d3 };
   auto sclk = hwlib::invert( _sclk );
   auto mosi = hwlib::target::pin_out{ hwlib::target::pins::d4 };
   
   auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso{ 
      sclk, mosi, hwlib::pin_in_dummy };
      
   //auto spi   = due::spi_bus(); 

   auto dc    = hwlib::target::pin_out{ hwlib::target::pins::d6 };
   auto & cs  = hwlib::pin_out_dummy;
   auto blk   = hwlib::target::pin_out{ hwlib::target::pins::d7 };
   auto rst   = hwlib::target::pin_out{ hwlib::target::pins::d5 };
   
   blk.write( 1 );blk.flush();

   auto display     = hwlib::st7789_spi_dc_cs_rst( spi, dc, cs, rst );   
   
   uint64_t start = hwlib::now_us();
   for(;;){

      hwlib::cout << "\n\n\n\n\n";

      start = hwlib::now_us();
      display.clear( hwlib::red );
      hwlib::cout << "Clear1 done in: " << ((hwlib::now_us() - start) / 1000) << " milliseconds\n";
      start = hwlib::now_us();
      display.flush();
      hwlib::cout << "Flush1 done in: " << ((hwlib::now_us() - start) / 1000) << " milliseconds\n"; 

      start = hwlib::now_us();
      display.clear( hwlib::green );
      hwlib::cout << "Clear2 done in: " << ((hwlib::now_us() - start) / 1000) << " milliseconds\n";
      start = hwlib::now_us();
      display.flush();
      hwlib::cout << "Flush2 done in: " << ((hwlib::now_us() - start) / 1000) << " milliseconds\n";

      start = hwlib::now_us();
      display.clear( hwlib::blue );
      hwlib::cout << "Clear3 done in: " << ((hwlib::now_us() - start) / 1000) << " milliseconds\n";
      start = hwlib::now_us();
      display.flush();
      hwlib::cout << "Flush3 done in: " << ((hwlib::now_us() - start) / 1000) << " milliseconds\n";
   }
   
}
