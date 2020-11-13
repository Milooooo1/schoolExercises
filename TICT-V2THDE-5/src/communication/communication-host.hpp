#ifndef COMMUNICATION_HOST_HPP_
#define COMMUNICATION_HOST_HPP_

#include "hwlib.hpp"
#include "communication.h"

class Host
{
    private:
        uint8_t u8CurrPlayer = 0;

        void broadcast_identify_msg(void);

        bool get_ack(void);

    public:
        Host(void);

        void assign_player_numbers(void);

        void start_game(uint32_t au32GameTime);

        void update(void);
};

#endif /* COMMUNICATION_HOST_HPP_ */