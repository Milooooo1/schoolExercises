#ifndef _TEXTINTERFACE_HPP
#define _TEXTINTERFACE_HPP

#include <iostream>
#include <array>
#include <stdlib.h>
#include "gameCore.hpp"
#include "def.hpp"

class textInterface{
private:
    gameCore game;
    void mainLoop();

    void printState();

public:
    textInterface(gameCore _game);

    void start();

};

#endif //_TEXTINTERFACE_HPP