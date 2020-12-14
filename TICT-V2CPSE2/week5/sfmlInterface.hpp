#ifndef _SFMLINTERFACE_HPP
#define _SFMLINTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "gameCore.hpp"
#include "naught.hpp"
#include "cross.hpp"
#include "grid.hpp"
#include "drawable.hpp"
#include "button.hpp"

class sfmlInterface{
private:
    gameCore game;
    int ply = 0; 
    bool finished = false;
    int winner = 0;

    void mainLoop();

    void endScreen(sf::RenderWindow & window);
public:

    sfmlInterface(gameCore _game);

    void start();

};

#endif //_SFMLINTERFACE_HPP