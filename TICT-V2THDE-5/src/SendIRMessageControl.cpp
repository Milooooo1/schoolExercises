#include "SendIRMessageControl.hpp"


/* -------------------------------- CONSTRUCTOR ---------------------------- */

SendIRMessageControl::SendIRMessageControl(PlayerData &arefPlayerData)
    :
    task("Send IR message control"),
    msgChannel(this, "Msg channel"),
    tim0(this, "timer 0"),
    refPlayerData(arefPlayerData),
    eCurrState(SND_STATE_IDLE)
    {}

/* ------------------------------ CONSTRUCTOR END -------------------------- */


/* ------------------------------ PRIVATE METHODS -------------------------- */

uint16_t SendIRMessageControl::compute_data(IR_MSG aeMSG)
{
    uint8_t u8PlayerNum = refPlayerData.getPlayerNumber();
    uint8_t u8WeaponDamage = refPlayerData.getWeaponInfo();

    uint16_t u16CheckSum = ((u8PlayerNum ^ u8WeaponDamage) << 11);

    return (u16CheckSum | (u8WeaponDamage << 6) | (u8PlayerNum << 1) | 0x1);
}


void SendIRMessageControl::send_bit(bool bToSend)
{
    IRLED.write(1);
    hwlib::wait_us(800 << bToSend);
    IRLED.write(0);
    hwlib::wait_us(1600 >> bToSend);
}


void SendIRMessageControl::send_data(uint16_t au16Data)
{
    for(int i = 15; i >= 0; i--)
    {
        send_bit( (au16Data & (0x1 << i))!= 0);
    }
}

/* ---------------------------- PRIVATE METHODS END ------------------------ */


/* ------------------------------ PUBLIC METHODS --------------------------- */

void SendIRMessageControl::send(IR_MSG eMSG)
{
    msgChannel.write(eMSG);
}

/* ---------------------------- PUBLIC METHODS END ------------------------- */


/* ------------------------------ STATE HANDLERS --------------------------- */

SendIRMessageControl::SND_STATE SendIRMessageControl::idle_handler(void)
{
    wait(msgChannel);
    IR_MSG eMSGToSend = msgChannel.read();

    u16Data = compute_data(eMSGToSend);
    u8CurrentIteration = 1;

    return SND_STATE_SEND;
}


SendIRMessageControl::SND_STATE SendIRMessageControl::send_handler(void)
{
    SND_STATE eNextState;

    send_data(u16Data);
    tim0.set(3000);

    if (u8CurrentIteration == 2)
    {
        eNextState = SND_STATE_IDLE;
    }
    else
    {
        wait(tim0);
        u8CurrentIteration++;

        eNextState = SND_STATE_SEND;
    }
    
    return eNextState;
}

/* ---------------------------- STATE HANDLERS END ------------------------- */


/* ------------------------------ STATE_MACHINE ---------------------------- */

void SendIRMessageControl::main(void)
{
    while (1)
    {
        switch(eCurrState)
        {
            case SND_STATE_IDLE:
                eCurrState = idle_handler();
                break;

            case SND_STATE_SEND:
                eCurrState = send_handler();
                break;

            default:
                break;
        }
    }
}

/* ---------------------------- STATE_MACHINE END -------------------------- */
