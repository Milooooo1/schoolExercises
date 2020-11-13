#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdint.h>


enum COMM_MSG 
{
    COMM_MSG_IDENTIFY,
    COMM_MSG_ASSIGN_PLAYER_NUM,
    COMM_MSG_GAME_START,
    COMM_MSG_SET_HITPOINTS,
    COMM_MSG_SET_SCORE,
    COMM_MSG_UPDATE,
    COMM_MSG_ACK,
    COMM_MSG_BROADCAST
};


enum UPDATE_EVENT
{
    UPDATE_EVENT_NONE,
    UPDATE_EVENT_SHOT,
    UPDATE_EVENT_HITPOINTS,
    UPDATE_EVENT_SCORE,
    UPDATE_EVENT_AMMO
};


struct MSG_PACKET
{
    uint8_t eType;
    uint8_t u8PlayerNum;
    uint8_t u8arrArgs[4];
    uint8_t bAnother;
};


#endif /* COMMUNICATION_H_ */
