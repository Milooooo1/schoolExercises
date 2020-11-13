#ifndef _PLAYERDATA_HPP
#define _PLAYERDATA_HPP

#include "hwlib.hpp"

/// @file

/// \brief
/// PlayerData Entity
/// \details
/// The PlayerData entity class consists off a few
/// getter and setter functions to store and get the data

class PlayerData
{
private:
    uint8_t internalPlayerNumber = 0, 
    internalWeaponInfo = 0, 
    internalPlayerHealth = 0;
    int internalGameTime;
    struct hit{
        int PlayerNumber;
        int WeaponInfo;
    };
    hit incommingHits[20]{};
    int internalhitCounter = 0;

public:

    /// \brief
    /// PlayerData constructor
    /// \details
    /// The PlayerData concstructor does not need anything
    /// it just sets and gets data.
    PlayerData();

    /// \brief
    /// setPlayerNumber()
    /// \details
    /// This is a setter function for the PlayerNumber
    void setPlayerNumber(uint8_t PlayerNumber);

    /// \brief
    /// setWeaponInfo()
    /// \details
    /// This is a setter function for the WeaponInfo
    void setWeaponInfo(uint8_t WeaponInfo);

    /// \brief
    /// setGameTime()
    /// \details
    /// This is a setter function for the GameTime
    void setGameTime(int GameTime);

    /// \brief
    /// setPlayerHealth()
    /// \details
    /// This is a setter function for the PlayerHealth
    void setPlayerHealth(uint8_t Health);

    /// \brief
    /// setHitCounter()
    /// \details
    /// This is a setter function for the hitCounter
    /// the hitcounter keeps track of the number of times
    /// a player has been hit, it corresponds to the 
    /// index of incomminghits array and its data. 
    void setHitCounter(int hitCounter);

    /// \brief 
    /// setIncommingHit()
    /// \details
    /// This is a setter function for a new incomming hit
    void setIncommingHit(int PlayerNumber, int WeaponInfo);

    /// \brief
    /// getPlayerNumber()
    /// \details
    /// This is a getter function for the PlayerNumber
    uint8_t getPlayerNumber();

    /// \brief
    /// getWeaponInfo()
    /// \details
    /// This is a getter function for the WeaponInfo
    uint8_t getWeaponInfo();

    /// \brief
    /// getGameTime()
    /// \details
    /// This is a getter functon for the GameTime
    int getGameTime();

    /// \brief
    /// getPlayerHealth()
    /// \details
    /// This is a getter function for the PlayerHealth
    uint8_t getPlayerHealth();

    /// \brief
    /// getHitCounter()
    /// \details
    /// This is a getter function for the hitCounter
    /// the hitcounter keeps track of the number of times
    /// a player has been hit, it corresponds to the 
    /// index of incomminghits array and its data. 
    int getHitCounter();

    /// \brief 
    /// getLastPlayerNumber()
    /// \details
    /// This is a getter function which returns
    /// the playerNumber of the player who most 
    /// recently hit you
    int getLastPlayerNumber();

    /// \brief 
    /// getLastWeaponInfo()
    /// \details
    /// This is a getter function which returns
    /// the weaponInfo of the player who most 
    /// recently hit you
    int getLastWeaponInfo();
};

#endif //_PLAYERDATA_HPP