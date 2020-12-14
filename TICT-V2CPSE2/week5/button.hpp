#ifndef _button_HPP
#define _button_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "drawable.hpp"

class button : public drawable {
public:
    bool isPressed = false;
    int pressedByPlayer = 0;

    button(sf::Vector2f _position, std::array<int, 2> _boardPos);

	void draw( sf::RenderWindow & window ) override;
    
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getCoords();

    void setButtonPressed(bool press, int player);
    void clearPress();
    std::array<int, 2> getBoardPosition();

private:
    sf::RectangleShape _button;
    sf::Vector2f position;
    sf::Vector2f size = sf::Vector2f(206,153);
    sf::Color color = sf::Color::Transparent;
    std::array<int, 2> boardPos;
};

#endif
