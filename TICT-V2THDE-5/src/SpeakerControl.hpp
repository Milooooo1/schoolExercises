#ifndef _SPEAKER_CONTROL_HPP
#define _SPEAKER_CONTROL_HPP

#include "rtos.hpp"
#include "hwlib.hpp"

/// @file

/// \brief
/// SpeakerControl task
/// \details
/// This task controls the speaker


/// \brief
/// Note class
/// \details
/// This class contains the possible notes you
/// can play. This is implemented to be more readable
class note {
public:

   // from https://www.seventhstring.com/resources/notefrequencies.html
   static const int A4  = 440;
   static const int A4s = 466;
   static const int B4  = 494;
   static const int C5  = 523;
   static const int C5s = 554;
   static const int D5  = 587;
   static const int D5s = 622;
   static const int E5  = 659;
   static const int F5  = 698;
   static const int F5s = 740;
   static const int G5  = 784;
   static const int G5s = 830;
   static const int A5  = 880;
   static const int A5s = 932;
   static const int B5  = 987;
   
   const int frequency;
    
   static const int dF = 1'000'000;  // full measure
   static const int dH = dF / 2;     // half measure
   static const int dQ = dF / 4;     // quarter measure     
   static const int d8 = dF / 24;     // 1/8 measure
   
   const int duration;
};

/// \brief
/// SpeakerControl class
/// \details
/// This class implements the speaker controller
/// it reacts to flags which are set by runGameControl
/// it can play 3 sounds, start, end and shoot sound.
class speakerControl : public rtos::task<>
{
private:
   hwlib::target::pin_out lsp = hwlib::target::pin_out(hwlib::target::pins::d8);
   rtos::flag shootSoundFlag, startSoundFlag, endSoundFlag;

   /// \brief
   /// playGameOverSound() function
   /// \details
   /// This function send the correct notes
   /// for the GameOverSound to the play function.
   void playGameOverSound(void);

   /// \brief
   /// playStartSound() function
   /// \details
   /// This function send the correct notes
   /// for the StartSound to the play function.
   void playStartSound(void);

   /// \brief
   /// playShootSound() function
   /// \details
   /// This function send the correct notes
   /// for the ShootSound to the play function.
   void playShootSound(void);

   /// \brief
   /// main loop function
   /// \details
   /// This function waits for the flags
   /// and if a flag has been set it plays the 
   /// corresponding sound
   void main(void);

public:

   /// \brief
   /// SpeakerControl constructor
   /// \details
   /// The controller needs a pin out for
   /// the speaker output.
   //The output pin is hardcoded for now, we were getting
   //errors with it. 
   speakerControl(/*hwlib::target::pin_out* speakerOutput*/);

   /// \brief
   /// play() function
   /// \details
   /// This function plays a desired note
   void play(const note &n);

   /// \brief
   /// setShootFlag() function
   /// \details
   /// This function sets the shootSoundFlag
   /// it is accessed by runGameControl
   /// the main function reacts to the flag
   /// being set.
   void setShootSoundFlag(void);

   /// \brief
   /// setStartFlag() function
   /// \details
   /// This function sets the shootStartFlag
   /// it is accessed by runGameControl
   /// the main function reacts to the flag
   /// being set.
   void setStartSoundFlag(void);

   /// \brief
   /// setStartFlag() function
   /// \details
   /// This function sets the shootStartFlag
   /// it is accessed by runGameControl
   /// the main function reacts to the flag
   /// being set.
   void setEndSoundFlag(void);
};

#endif // _SPEAKER_CONTROL_HPP