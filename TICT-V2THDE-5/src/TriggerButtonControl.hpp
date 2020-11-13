#ifndef _TRIGGERBUTTONCONTROL_HPP
#define _TRIGGERBUTTONCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "RunGameControl.hpp"
#include "PlayerData.hpp"

/// @file

/// \brief
/// TriggerButtonControl task
/// \details
/// This task controls the triggerButton
/// it makes sure the button is checked
/// every 50ms (excluding the 80ms debounce)
/// delay. This ensures a much better using 
/// experience for the trigger button.

class TriggerButtonControl : rtos::task<> {
private:
    hwlib::target::pin_in *input;
    RunGameControl *runGame;
    PlayerData &refPlayerData;

    /// \brief
    /// Main loop
    /// \details
    /// The main loop for the TriggerButtonControl
    /// implements the triggerButton. 
    void main();

public:

    /// \brief
    /// TriggerButtonControl contructor
    /// \details
    /// The constructor for the TriggerButtonControl
    /// needs an input pin from which to read from
    /// and a runGameControl task which he uses
    /// to set a flag. 
    TriggerButtonControl(hwlib::target::pin_in *input,
                         RunGameControl *runGame,
                         PlayerData &arefPlayerData);

};

#endif // TRIGGERBUTTONCONTROL