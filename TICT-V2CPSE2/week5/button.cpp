#include <SFML/Graphics.hpp>
#include "button.hpp"

button::button(sf::Vector2f _position, std::array<int, 2> _boardPos):
    drawable(),
    position(_position),
    boardPos(_boardPos)
{}

void button::draw( sf::RenderWindow & window ) {
    _button.setSize(size);
    _button.setPosition(position);
    _button.setFillColor(color);
    window.draw(_button);
}


sf::FloatRect button::getGlobalBounds(){
    return _button.getGlobalBounds();
}

sf::Vector2f button::getCoords(){
    return position + sf::Vector2f(20, 20);
}

void button::setButtonPressed(bool pressed, int player){
    isPressed = true;
    pressedByPlayer = player;
}

void button::clearPress(){
    isPressed = false;
    pressedByPlayer = 0;
}


std::array<int, 2>  button::getBoardPosition(){
    return boardPos;
}