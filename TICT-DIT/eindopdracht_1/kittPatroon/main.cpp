#include "hwlib.hpp"

int main( void ){
auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

auto bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

uint8_t address = 0x38;
int counter = 0;


while(1){
    auto poort = ((hwlib::i2c_bus*)(&bus))->write(address);
    switch (counter) {
    case 0: poort.write(0x01);
        break;
    case 1: poort.write(0x03);
        break;
    case 2: poort.write(0x06);
        break;
    case 3: poort.write(0x0C);
        break;
    case 4: poort.write(0x08);
        break;
    case 5: poort.write(0x0C);
        break;
    case 6: poort.write(0x06);
        break;
    case 7: poort.write(0x03);
        break;
    default: counter = 0;

    }
    counter++;
    hwlib::wait_ms( 200 );
    }
}
