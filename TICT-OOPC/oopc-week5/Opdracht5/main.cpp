#include "hwlib.hpp"
#include "pin_out_invert.hpp"

int main( void ){	   
   
    auto ds   = hwlib::target::pin_out( hwlib::target::pins::d9 );
    auto shcp = hwlib::target::pin_out( hwlib::target::pins::d7 );
    auto stcp = hwlib::target::pin_out( hwlib::target::pins::d8 );
    auto led1 = hwlib::target::pin_out( hwlib::target::pins::d2 );
    auto led2 = hwlib::target::pin_out( hwlib::target::pins::d3 );
    auto led3 = hwlib::target::pin_out( hwlib::target::pins::d4 );
    auto led4 = hwlib::target::pin_out( hwlib::target::pins::d5 );
    auto led1_invert = pin_out_invert( led1 );
    auto led2_invert = pin_out_invert( led2 );
    auto led3_invert = pin_out_invert( led3 );
    auto led4_invert = pin_out_invert( led4 );
    auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso( 
       shcp, 
       ds, 
       hwlib::pin_in_dummy 
    );
    
    auto hc595 = hwlib::hc595( spi, stcp );
    
    auto leds = hwlib::all(hc595.p7, hc595.p6, hc595.p5 ,hc595.p4, led4_invert, led3_invert, led2_invert, led1_invert );

    hwlib::blink(leds);   

    //Dit is Opdracht 4
    // auto half1 = hwlib::all(led4, led3, led2, led1);
    // auto half2 = hwlib::all(hc595.p7, hc595.p6, hc595.p5, hc595.p4);

    // auto leds = hwlib::port_out_from( 
    //     half1,
    //     half2
    // );
    // hwlib::kitt(leds, 400);
}
