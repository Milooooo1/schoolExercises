#ifndef SEND_IR_MESSAGE_CONTROL_HPP_
#define SEND_IR_MESSAGE_CONTROL_HPP_

#include "rtos.hpp"

#include "PlayerData.hpp"

/// @file

enum IR_MSG
{
    IR_MSG_SHOOT
};

class SendIRMessageControl : public rtos::task<256>
{
    private:
        enum SND_STATE 
        {
            SND_STATE_IDLE,
            SND_STATE_SEND
        };

        rtos::channel<IR_MSG, 4> msgChannel;
        rtos::timer tim0;

        PlayerData &refPlayerData;        

        SND_STATE eCurrState;

        hwlib::target::d2_36kHz IRLED;
        uint16_t u16Data;
        uint8_t u8CurrentIteration;

        uint16_t compute_data(IR_MSG aeMSG);

        void send_bit(bool bToSend);
        void send_data(uint16_t au16Data);

        SND_STATE idle_handler(void);
        SND_STATE send_handler(void);

        void main(void) override;

    public:
        SendIRMessageControl(PlayerData &arefPlayerData);


        /**********************************************//**
        * @brief
        *  Sends out a IR_MSG, filling out the bitfields
        *  by using the reference to PlayerData that has
        *  been supplied to the class in the constructor.
        **************************************************/
        void send(IR_MSG eMSG);
};

#endif /* SEND_IR_MESSAGE_CONTROL_HPP_ */