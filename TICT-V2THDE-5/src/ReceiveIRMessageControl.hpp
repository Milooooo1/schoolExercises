#ifndef RECEIVE_IR_MESSAGE_CONTROL_HPP
#define RECEIVE_IR_MESSAGE_CONTROL_HPP

#include "rtos.hpp"

#include "FIFO.hpp"
#include "RunGameControl.hpp"

/// @file

enum IR_MESSAGE_TYPE 
{
    IR_MESSAGE_TYPE_HIT,
    IR_MESSAGE_TYPE_GAMETIME
};

/******************************************************//**
* @brief
*  Control object that processes incoming data.
* @details
*  Control object that processes incoming IR data.
*  It doesn't have an interface because it only decodes
*  the data, the decoded message is then sent to the
*  control object that is tasked with processing the
*  message. This is done to promote loose coupling.
**********************************************************/
class ReceiveIRMessageControl : public rtos::task<512>
{
    private:
        enum RECV_STATE 
        {
            RECV_STATE_IDLE,
            RECV_STATE_RECEIVE
        };
        
        struct timeData
        {
            bool bState;
            uint16_t u16Period;
        };

        rtos::timer tim0;

        RunGameControl& refRunGameControl;
        hwlib::pin_in& refReceiver;

        FIFO<timeData, 32> timeFIFO;
       
        RECV_STATE eCurrState;
        bool bLastState;
        uint16_t u16LastMSG;
        uint8_t u8CheckSum;
        unsigned uNumReceived;
        unsigned uNumCycles;

        uint16_t extract_data_from_FIFO();

        uint8_t compute_checksum(uint16_t au16Data);
        uint8_t extract_checksum(uint16_t au16Data);

        RECV_STATE idle_handler(void);
        RECV_STATE receive_handler(void);

        void main(void) override;

    public:
        ReceiveIRMessageControl(
            RunGameControl& refRunGameControl,
            hwlib::pin_in& refReceiver);
};

#endif /* RECEIVE_IR_MESSAGE_CONTROL_HPP */