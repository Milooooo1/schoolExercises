#include "communication-host.hpp"
#include "NRF.h"

#include "SPI-due.hpp"
#include "due-PIO.h"

#define DEBUG
#include "log.hpp"

/* --------------------------- Constructor --------------------------------- */

Host::Host(void)
{
    NRF_setup(  &SPI_INTERFACE_DUE, 0, &GPIO_INTERFACE_DUE, 
                0, 10, 0, 17, 22, sizeof(MSG_PACKET));
}

/* ------------------------- Constructor end ------------------------------- */


/* ------------------------- Private methods ------------------------------- */

void Host::broadcast_identify_msg(void)
{
    LOG("Sending identify msg");

    NRF_enter_transmit_mode();

    MSG_PACKET msg =
    {
        COMM_MSG_IDENTIFY,
        0,
        {0,0,0,0},
        0
    };

    NRF_write_data((uint8_t*)&msg);

    MSG_PACKET receivedData;

    NRF_enter_receive_mode();

    for(int i = 0; i < 3000; i++)
    {
        if(NRF_read_data((uint8_t*)&receivedData) == NRF_STATUS_OK)
        {
            LOG("got response");
            LOG(receivedData.u8arrArgs[0]);

            receivedData.eType = COMM_MSG_ASSIGN_PLAYER_NUM;
            receivedData.u8PlayerNum = u8CurrPlayer++;

            NRF_enter_transmit_mode();

            NRF_write_data((uint8_t*)&receivedData);

            get_ack();

            NRF_enter_receive_mode();
            
            hwlib::wait_ms(1);
        }

        hwlib::wait_ms(1);
    }
}


bool Host::get_ack(void)
{
    NRF_enter_receive_mode();

    MSG_PACKET msg;

    while(1)
    {
        if(NRF_read_data((uint8_t*)&msg) == NRF_STATUS_OK)
        {
            if(msg.eType == COMM_MSG_ACK)
            {
                LOG("MSG aknowledged");

                return true;
            }
            else
            {
                LOG("ERROR: msg not acknowledged");

                return false;
            }
        }
    }
    NRF_enter_transmit_mode();    
}

/* ----------------------- Private methods end ----------------------------- */


/* -------------------------- Public methods ------------------------------- */

void Host::assign_player_numbers(void)
{
    broadcast_identify_msg();
}


void Host::start_game(uint32_t au32GameTime)
{
    NRF_enter_transmit_mode();

    MSG_PACKET msg =
    {
        COMM_MSG_BROADCAST,
        0,
        {0,0,0,0},
        0
    };


    NRF_write_data((uint8_t*)&msg);

    NRF_enter_receive_mode();
    
    LOG("Sending game start");

    for(int i = 0; i < 3000; i++)
    {
        if(NRF_read_data((uint8_t*)&msg) == NRF_STATUS_OK)
        {
            LOG("got response");

            NRF_enter_transmit_mode();

            msg.eType = COMM_MSG_GAME_START;
            *(uint32_t*)msg.u8arrArgs = au32GameTime;

            NRF_write_data((uint8_t*)&msg);

            get_ack();

            NRF_enter_receive_mode();

            hwlib::wait_ms(1);
        }

        hwlib::wait_ms(1);
    }
}


void Host::update(void)
{
    NRF_enter_transmit_mode();


    LOG("Asking for update data");

    MSG_PACKET msg =
    {
        COMM_MSG_BROADCAST,
        0,
        {0,0,0,0},
        0
    };

    NRF_write_data((uint8_t*)&msg);

    NRF_enter_receive_mode();

    for(int i = 0; i < 3000; i++)
    {
        if(NRF_read_data((uint8_t*)&msg) == NRF_STATUS_OK)
        {
            LOG("got response");

            NRF_enter_transmit_mode();

            msg.eType = COMM_MSG_UPDATE;

            NRF_write_data((uint8_t*)&msg);

            NRF_enter_receive_mode();

            for(unsigned j = 0; j < 1000; j++)
            {
                NRF_read_data((uint8_t*)&msg);

                if(msg.eType == COMM_MSG_ACK)
                {
                    LOG("No further data to be read");
                    j = 1000;
                }
                else if(msg.eType == COMM_MSG_UPDATE && 
                        msg.u8arrArgs[0] == UPDATE_EVENT_SHOT)
                {
                    LOG("update received");

                    hwlib::cout << "player ";
                    hwlib::cout << msg.u8PlayerNum;
                    hwlib::cout << " got hit by player ";
                    hwlib::cout << msg.u8arrArgs[1];
                    hwlib::cout << " and received ";
                    hwlib::cout << msg.u8arrArgs[2];
                    hwlib::cout << " damage. \n";

                    msg.u8arrArgs[0] = UPDATE_EVENT_NONE;
                }

                hwlib::wait_us(1);
            }
        }

        hwlib::wait_ms(1);
    }
}

/* ------------------------ Public methods end ----------------------------- */

