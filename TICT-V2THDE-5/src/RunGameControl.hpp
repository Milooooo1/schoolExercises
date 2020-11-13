#ifndef RUN_GAME_CONTROL_HPP_
#define RUN_GAME_CONTROL_HPP_

#include "rtos.hpp"

#include "SendIRMessageControl.hpp"
#include "FIFO.hpp"

#include "display.hpp"
#include "SpeakerControl.hpp"

/// @file

/******************************************************//**
* @brief
*  Packs data relevant to a HIT msg into single object.
**********************************************************/
struct HIT
{
    uint8_t player;
    uint8_t firePower;
};


/******************************************************//**
* @brief
*  Control object that contains game logic.
* @details
*  This object contains the games logic. It is also tasked
*  with relaying the game info to the player, to do so
*  it keeps a reference to a Display and speaker.
**********************************************************/
class RunGameControl : public rtos::task<256>
{
    private:
        enum RUN_GAME_STATE
        {
            RUN_GAME_STATE_INACTIVE,
            RUN_GAME_STATE_IDLE,
            RUN_GAME_STATE_SHOOT
        };

        rtos::flag startFlag;
        rtos::flag triggerFlag;
        rtos::channel<HIT, 4> hitChannel;
        rtos::timer tim0;

        SendIRMessageControl &IRSender;
        PlayerData &refPlayerData;
        Display &refDisplay;
        speakerControl &refSpeaker;

        FIFO<HIT, 8> hitFIFO;

        RUN_GAME_STATE eCurrState;
        uint32_t u32GameTime;
        int32_t i32NextShotDelay;
        int32_t i32NextHitDelay;
        int32_t i32PlayerLifes;

        void signal_game_start(void);
        void signal_game_end(void);
        uint32_t compute_shot_delay(void);
        uint32_t compute_hit_delay(void);

        RUN_GAME_STATE inactive_handler(void);
        RUN_GAME_STATE idle_handler(void);
        RUN_GAME_STATE shoot_handler(void);

        void main(void) override;
    
    public:
        RunGameControl(
            SendIRMessageControl &refSendControl,
            PlayerData &arefPlayerData,
            Display &arefDisplay,
            speakerControl &arefSpeaker
            );
    

        /**********************************************//**
        * @brief
        *  Sets the startFlag and initialises u32Gametime,
        *  which in turn start the game by switching to
        *  the RUN_GAME_STATE_IDLE state.
        **************************************************/
        void start_game(uint32_t au32GameTime);


        /**********************************************//**
        * @brief
        *  Sets the triggerFlag, which switches the
        *  system to the RUN_GAME_STATE_SHOOT.
        **************************************************/
        void shoot(void);


        /**********************************************//**
        * @brief
        *  Writes hit into hitChannel.
        **************************************************/
        void hit(HIT hitToWrite);


        /**********************************************//**
        * @brief
        *  Returns the oldest hit 
        *  that hasn't yet been read.
        * @details
        *  This function keeps us from having to keep a
        *  reference to the RFTranceiver,
        *  which would create a circular dependency.
        **************************************************/
        HIT *get_recent_hit(void);
};

#endif /* RUN_GAME_CONTROL_HPP_ */