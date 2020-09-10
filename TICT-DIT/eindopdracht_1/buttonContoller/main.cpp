#include "hwlib.hpp"

int main( void ){
auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

auto bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

uint8_t address = 0x38;
uint8_t result[1];
uint8_t poort_value = 0;

while(1){
	{
	    auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
        writetr.write(0x00);
	    writetr.write(0x10);
	}
	{
    	auto readtr = ((hwlib::i2c_bus*)(&bus))->read(address);
    	readtr.read(result, 1);
	}
    poort_value = result[0];
    hwlib::wait_ms(200);
    hwlib::cout << "Button value = " << hwlib::hex << poort_value  << "\n";
    if(poort_value != 0x10){
	    {
	    auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
	    writetr.write(0x0F);
        hwlib::cout << "Lights on"  << "\n";
        hwlib::wait_ms(4000);
        writetr.write(0x00);
        hwlib::cout << "Lights out"  << "\n";
	    }
    }
}
}
