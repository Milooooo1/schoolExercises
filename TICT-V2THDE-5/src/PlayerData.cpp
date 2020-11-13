#include "PlayerData.hpp"

PlayerData::PlayerData() {}

void PlayerData::setPlayerNumber(uint8_t PlayerNumber)
{
    internalPlayerNumber = PlayerNumber;
}

void PlayerData::setWeaponInfo(uint8_t WeaponInfo)
{
    internalWeaponInfo = WeaponInfo;
}

void PlayerData::setGameTime(int GameTime)
{
    internalGameTime = GameTime; 
}

void PlayerData::setPlayerHealth(uint8_t PlayerHealth)
{
    internalPlayerHealth = PlayerHealth;
}

void PlayerData::setHitCounter(int hitCounter)
{  
    internalhitCounter = hitCounter;
}

void PlayerData::setIncommingHit(int PlayerNumber, int WeaponInfo)
{
    incommingHits[internalhitCounter].PlayerNumber = PlayerNumber;
    incommingHits[internalhitCounter].WeaponInfo = WeaponInfo;
}

uint8_t PlayerData::getPlayerNumber()
{
    return internalPlayerNumber;
}

uint8_t PlayerData::getWeaponInfo()
{
    return internalWeaponInfo;
}

int PlayerData::getGameTime()
{
    return internalGameTime;
}

uint8_t PlayerData::getPlayerHealth()
{
    return internalPlayerHealth;
}

int PlayerData::getHitCounter()
{
    return internalhitCounter;
}

int PlayerData::getLastPlayerNumber()
{
    return incommingHits[internalhitCounter].PlayerNumber;
}

int PlayerData::getLastWeaponInfo()
{
    return incommingHits[internalhitCounter].WeaponInfo;
}