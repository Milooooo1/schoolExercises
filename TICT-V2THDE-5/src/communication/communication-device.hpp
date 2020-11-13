#ifndef COMMUNICATION_DEVICE_HPP_
#define COMMUNICATION_DEVICE_HPP_

#include "communication.h"

#include "hwlib.hpp"
#include "rtos.hpp"

#include "RunGameControl.hpp"
#include "PlayerData.hpp"

#include "FIFO.hpp"

class RFTransceiver : public rtos::task<512>
{
    private:
        RunGameControl *pRunGameConrol;
        PlayerData *pPlayerData;
        
        inline static uint64_t u64SerialNum = 0;
    
        void identify_handler(MSG_PACKET *msg);
        
        /* Must be placed in ram, rewrites part of the flash memory,
            Can't be inlined because that would mean that it is placed
            in flash. */
        static  __attribute__((section(".data"))) 
                __attribute__ ((noinline)) void get_serial(void);

        void assign_player_num_handler(MSG_PACKET *msg);

        void game_start_handler(MSG_PACKET *msg);

        void get_hitpoints_handler(MSG_PACKET *msg);

        void set_hitpoints_handler(MSG_PACKET *msg);

        void get_score_handler(MSG_PACKET *msg);

        void set_scrore_handler(MSG_PACKET *msg);

        void update_handler(MSG_PACKET *msg);

        void broadcast_handler(MSG_PACKET *msg);

        void main(void) override;

    public:
        RFTransceiver(RunGameControl *apRunGameConrol, PlayerData *apPlayerData);
        
};

#endif /* COMMUNICATION_DEVICE_HPP_ */
