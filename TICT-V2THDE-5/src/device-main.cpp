#include "hwlib.hpp"
#include "rtos.hpp"
#include "ReceiveIRMessageControl.hpp"
#include "SendIRMessageControl.hpp"
#include "RunGameControl.hpp"
#include "TriggerButtonControl.hpp"
#include "communication/communication-device.hpp"
#include "communication/communication-host.hpp"
#include "display.hpp"
#include "SpeakerControl.hpp"

#define DEBUG

#include "log.hpp"

int main( void ){	
    auto scl          = hwlib::target::pin_oc( hwlib::target::pins::d6 );
    auto sda          = hwlib::target::pin_oc( hwlib::target::pins::d7 );                                                                                                                                                              
   // auto i2c_bus      = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );                                                                                                                                                                  
   // auto w            = hwlib::glcd_oled( i2c_bus, 0x3c );                   
   auto sw           = hwlib::target::pin_in( hwlib::target::pins::d43 );
   auto IR_Receiver  = hwlib::target::pin_in( hwlib::target::pins::d5  ); 

   hwlib::wait_ms(500);
   
   hwlib::i2c_bus_bit_banged_scl_sda bus(scl, sda);
   Display d(bus);

   auto data = PlayerData();
   auto speaker = speakerControl();
   auto send = SendIRMessageControl(data);
   auto runGameControl = RunGameControl(send, data, d, speaker);
   auto receive = ReceiveIRMessageControl(runGameControl, IR_Receiver);
   auto trigger = TriggerButtonControl(&sw, &runGameControl, data);

   auto transceiver = RFTransceiver(&runGameControl, &data);



   rtos::display_statistics();
   rtos::run();
}


// int main(void)
// {
//     hwlib::wait_ms(500);
//     hwlib::cout << "Please enter the duration of the match: ";
    
//     unsigned i = 0;
//     uint32_t u32GameLen = 0;

//     char input;
//     char buffer[5] = {0};
//     while(1)
//     {
//         hwlib::cin >> input;
//         if(input == '\n')
//             break;
//         buffer[i++] = (input - 0x30);
//     }

//     for(int j = (i-1), acc = 1; j >= 0; --j)
//     {
//         u32GameLen += buffer[j] * acc;
//         acc *= 10;
//     }

//     hwlib::cout << "\nMatch lasts: ";
//     hwlib::cout << u32GameLen;
//     hwlib::cout << " seconds\n";

//     hwlib::wait_ms(100);
//     Host h;
//     hwlib::wait_ms(100);
//     h.assign_player_numbers();
//     hwlib::wait_ms(1000);

//    h.start_game(u32GameLen);
//    hwlib::wait_ms(1000);

//    while(1)
//    {
//       h.update();
//       hwlib::wait_ms(1000);
//    }
// }