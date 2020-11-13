#include "RunGameControl.hpp"

#define DEBUG
#include "log.hpp"

/* -------------------------------- CONSTRUCTOR ---------------------------- */

RunGameControl::RunGameControl(
    SendIRMessageControl &refSendControl,
    PlayerData &arefPlayerData,
    Display &arefDisplay,
    speakerControl &arefSpeaker)
    :
    task("Run game control"),
    startFlag(this),
    triggerFlag(this),
    hitChannel(this),
    tim0(this),
    IRSender(refSendControl),
    refPlayerData(arefPlayerData),
    refDisplay(arefDisplay),
    refSpeaker(arefSpeaker),
    eCurrState(RUN_GAME_STATE_INACTIVE),
    i32PlayerLifes(20)
    {}

/* ------------------------------ CONSTRUCTOR END -------------------------- */


/* ------------------------------ PRIVATE METHODS -------------------------- */

void RunGameControl::signal_game_start(void)
{
    LOG("Match started.");
    refSpeaker.setStartSoundFlag();
    refDisplay.render_start();
}


void RunGameControl::signal_game_end(void)
{
    refSpeaker.setEndSoundFlag();
    refDisplay.render_end();
}


uint32_t RunGameControl::compute_shot_delay(void)
{
    return (refPlayerData.getWeaponInfo() * 3);
}


uint32_t RunGameControl::compute_hit_delay(void)
{
    return 2;
}

/* ---------------------------- PRIVATE METHODS END ------------------------ */


/* ------------------------------ PUBLIC METHODS --------------------------- */

void RunGameControl::start_game(uint32_t au32GameTime)
{
    u32GameTime = au32GameTime;
    startFlag.set();
}


void RunGameControl::shoot(void)
{
    triggerFlag.set();
}


void RunGameControl::hit(HIT hitToWrite)
{
    hitChannel.write(hitToWrite);
}


HIT *RunGameControl::get_recent_hit(void)
{
    return hitFIFO.read();
}

/* ---------------------------- PUBLIC METHODS END ------------------------- */


/* ------------------------------ STATE HANDLERS --------------------------- */

RunGameControl::RUN_GAME_STATE RunGameControl::inactive_handler(void)
{
    wait(startFlag);
    
    signal_game_start();

    i32NextHitDelay = 0;
    i32NextShotDelay = 0;
    i32PlayerLifes = 20;

    return RUN_GAME_STATE_IDLE;
}


RunGameControl::RUN_GAME_STATE RunGameControl::idle_handler(void)
{
    refDisplay.render_lifes((uint8_t)i32PlayerLifes);
    refDisplay.render_time(u32GameTime);
    RUN_GAME_STATE eNextState;
    tim0.set(1000000);

    rtos::event event = wait(triggerFlag + hitChannel + tim0 );
    
    if(event == triggerFlag)
    {
        if(i32NextShotDelay <= 0)
        {
            eNextState = RUN_GAME_STATE_SHOOT;
        }
        else
        {
            eNextState = RUN_GAME_STATE_IDLE;
        }
    }
    else if(event == hitChannel)
    {
        HIT lastHit = hitChannel.read();

        if(i32NextHitDelay <= 0)
        {
            eNextState = RUN_GAME_STATE_IDLE;

            /* Don't process messages sent by player */
            if(lastHit.player != refPlayerData.getPlayerNumber())
            {
                LOG("Got hit by player num: ")
                LOG(lastHit.player)

                i32PlayerLifes -= lastHit.firePower;
                i32NextHitDelay = compute_hit_delay();

                LOG(i32PlayerLifes)
                LOG("lifes left")

                hitFIFO.push_back(lastHit);

                if(i32PlayerLifes <= 0)
                {
                    signal_game_end();
                    eNextState = RUN_GAME_STATE_INACTIVE;
                }
            }
        }
        else
        {
            eNextState = RUN_GAME_STATE_IDLE;
        }
    }
    else
    {
        u32GameTime--;
        i32NextShotDelay--;
        i32NextHitDelay--;

        if(u32GameTime == 0)
        {
            signal_game_end();
            eNextState = RUN_GAME_STATE_INACTIVE;
        }
        else
        {
            eNextState = RUN_GAME_STATE_IDLE;
        }
    }

    return eNextState;
}


RunGameControl::RUN_GAME_STATE RunGameControl::shoot_handler(void)
{
    LOG("shot");
    refSpeaker.setShootSoundFlag();
    IRSender.send(IR_MSG_SHOOT);
    i32NextShotDelay = compute_shot_delay();

    return RUN_GAME_STATE_IDLE;
}

/* ---------------------------- STATE HANDLERS END ------------------------- */


/* ------------------------------ STATE_MACHINE ---------------------------- */

void RunGameControl::main(void)
{
    while(1)
    {
        switch (eCurrState)
        {
            case RUN_GAME_STATE_INACTIVE:
                eCurrState = inactive_handler();
                break;

            case RUN_GAME_STATE_IDLE:
                eCurrState = idle_handler();
                break;
            
            case RUN_GAME_STATE_SHOOT:
                eCurrState = shoot_handler();
                break;

            default:
                break;
        }
    }
}

/* ---------------------------- STATE_MACHINE END -------------------------- */
