#ifndef _AI_HPP_
#define _AI_HPP_

#define BUFFER_SIZE 1024

enum DIRECTION 
{
    LEFT = 0,
    UP = 1,
    RIGHT =  2
};

enum STATE_MACHINE
{
    FSM_IDLE = 0,
    FSM_HAS_ROOM = 1,
    FSM_HAS_SMELL = 2,
    FSM_HAS_DIRECTIONS = 3,
    FSM_PRESENTED_CHOICE = 4,
    FSM_ACTION_PROMPT = 5,
    FSM_ROOM_PROMPT = 6
};

namespace AI
{
    /* 
    * Copies arguments into the module
    * game excecutable at [0] and 
    * number of matches at [1] this data
    * should be validated before passing it
    * to this function.
    * */
    void init(const char* arguments[]);

    /* 
    * Starts a new match
    * */
    void start(void);

    /*
    * Replays previous match
    * */
    void restart(void);


    void cleanup(void);

};

#endif