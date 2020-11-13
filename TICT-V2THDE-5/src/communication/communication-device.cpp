#include "communication-device.hpp"

#include "../SPI/SPI-due.hpp"
#include "../drivers/IO/due-PIO.h"

#include "../drivers/NRF24L01+/NRF.h"

#define DEBUG
#include "log.hpp"

/* ----------------------------- HELPER FUNCTIONS -------------------------- */

static void send_ack()
{
    NRF_enter_transmit_mode();
    hwlib::wait_us(100);

    /* We don't care about the value of other fields. */
    MSG_PACKET ackPacket = {COMM_MSG_ACK};
    NRF_write_data((uint8_t*)&ackPacket);

    NRF_enter_receive_mode();
}

/* --------------------------- HELPER FUNCTIONS END ------------------------ */


/* ----------------------------- PRIVATE METHODS --------------------------- */

void RFTransceiver::get_serial(void)
{
    EFC0->EEFC_FCR = EEFC_FCR_FCMD_STUI | EEFC_FCR_FKEY_PASSWD;
    while((EFC0->EEFC_FSR & EEFC_FSR_FRDY) != 0);

    u64SerialNum = *(uint64_t*)(0x80000);

    EFC0->EEFC_FCR = EEFC_FCR_FCMD_SPUI | EEFC_FCR_FKEY_PASSWD;
    while((EFC0->EEFC_FSR & EEFC_FSR_FRDY) == 0);
}


///////////////////////////////////////
// MSG HANDLERS

void RFTransceiver::identify_handler(MSG_PACKET *msg)
{
    if(u64SerialNum == 0)
    {
        get_serial();
    }
    
    hwlib::wait_ms_busy(u64SerialNum % 2000);

    NRF_enter_transmit_mode();

    uint8_t *pSerialNum = (uint8_t*)&u64SerialNum;

    MSG_PACKET response = {
        COMM_MSG_IDENTIFY, 
        0, 
        {pSerialNum[0],pSerialNum[1],pSerialNum[2],pSerialNum[3]}, 
        0};
    NRF_write_data((uint8_t*)&response);

    NRF_enter_receive_mode();
}


void RFTransceiver::assign_player_num_handler(MSG_PACKET *msg)
{
    uint32_t *u32Recipient = (uint32_t*)msg->u8arrArgs;

    if((uint32_t)(u64SerialNum & 0xFFFFFFFF) == *u32Recipient)
    {
        pPlayerData->setPlayerNumber(msg->u8PlayerNum);

        LOG("got assigned");
        LOG(pPlayerData->getPlayerNumber());

        send_ack();
    }

}


void RFTransceiver::game_start_handler(MSG_PACKET *msg)
{       
    pRunGameConrol->start_game((*(uint32_t*)msg->u8arrArgs));
    
    hwlib::wait_ms_busy(u64SerialNum % 3000);

    send_ack();
}


void RFTransceiver::set_hitpoints_handler(MSG_PACKET *msg)
{
    pPlayerData->setPlayerHealth(msg->u8arrArgs[0]);
}


void RFTransceiver::set_scrore_handler(MSG_PACKET *msg)
{
}


void RFTransceiver::update_handler(MSG_PACKET *msg)
{
    NRF_enter_transmit_mode();
    HIT *pHitToSend = pRunGameConrol->get_recent_hit();

    while(pHitToSend != nullptr)
    {
        hwlib::wait_us(100);

        MSG_PACKET msgToSend =
        {
            COMM_MSG_UPDATE,
            pPlayerData->getPlayerNumber(),
            {
                UPDATE_EVENT_SHOT, 
                pHitToSend->player, 
                pHitToSend->firePower,
                0
            },
            true
        };
        
        NRF_write_data((uint8_t*)&msgToSend);

        pHitToSend = pRunGameConrol->get_recent_hit();
    }

    NRF_enter_receive_mode();

    /* TODO send hitpoints too */

    /* Send ack ends notifies host that no 
        further messages will be send. */
    send_ack();
}


void RFTransceiver::broadcast_handler(MSG_PACKET *msg)
{
    MSG_PACKET msgToSend =
    {
        COMM_MSG_ACK,
        pPlayerData->getPlayerNumber(),
        {0,0,0,0},
        false
    };

    NRF_enter_transmit_mode();

    hwlib::wait_ms(u64SerialNum % 3000);

    NRF_write_data((uint8_t*)&msgToSend);

    NRF_enter_receive_mode();
}


/* --------------------------- PRIVATE METHODS END ------------------------- */


/* ----------------------------- PUBLIC METHODS ---------------------------- */

RFTransceiver::RFTransceiver(RunGameControl *apRunGameControl, PlayerData *apPlayerData)
    :   task(0, "Tranceiver task"),
        pRunGameConrol(apRunGameControl),
        pPlayerData(apPlayerData)
{
    NRF_setup(  &SPI_INTERFACE_DUE, 0, &GPIO_INTERFACE_DUE, 
                0, 10, 0, 17, 22, sizeof(MSG_PACKET));
    
    NRF_enter_receive_mode();
}


void RFTransceiver::main(void)
{
    while(1)
    {
        MSG_PACKET msg = {0};
        
        if( NRF_read_data((uint8_t*)&msg) == NRF_STATUS_OK)
        {
            switch(msg.eType)
            {
                case COMM_MSG_IDENTIFY:
                    identify_handler(&msg);
                    break;

                case COMM_MSG_ASSIGN_PLAYER_NUM:
                    assign_player_num_handler(&msg);
                    break;
                
                case COMM_MSG_GAME_START:
                    game_start_handler(&msg);
                    break;
                
                case COMM_MSG_SET_HITPOINTS:
                    set_hitpoints_handler(&msg);
                    break;

                case COMM_MSG_SET_SCORE:
                    set_scrore_handler(&msg);
                    break;

                case COMM_MSG_UPDATE:
                    update_handler(&msg);
                    break;

                case COMM_MSG_BROADCAST:
                    broadcast_handler(&msg);

                default:
                    break; 
            }
        }

        hwlib::wait_us(600);
    }
}

/* --------------------------- PUBLIC METHODS END -------------------------- */
