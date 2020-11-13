#include "TriggerButtonControl.hpp"

TriggerButtonControl::TriggerButtonControl(
    hwlib::target::pin_in *input,
    RunGameControl *runGame,
    PlayerData &arefPlayerData) 
    : 
    task(4, "TriggerButtonControl"),
    input(input),
    runGame(runGame),
    refPlayerData(arefPlayerData)
{
}

void TriggerButtonControl::main()
{
    for (;;)
    {
        hwlib::wait_ms(50);
        input->refresh();
        hwlib::wait_ms(80);
        if (!input->read())
        {
            uint8_t u8Pow = 0;
            while(!input->read())
            {
                if(u8Pow < 5)
                {
                    u8Pow++;
                }

                hwlib::wait_ms(500);
            }
            refPlayerData.setWeaponInfo(u8Pow);
            runGame->shoot();
        }
    }
}