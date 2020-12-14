#include <SFML/Graphics.hpp>
#include "cross.hpp"

cross::cross( sf::Vector2f position, sf::Vector2f size, sf::Color color):
    drawable(),
    position(position),
    size(size),
    color(color)
{}

void cross::draw( sf::RenderWindow & window ) {

    diagonal1[0].position = sf::Vector2f(position);
    diagonal1[0].color = sf::Color(color);
    diagonal1[1].position = sf::Vector2f(size.x + position.x, size.y + position.y);
    diagonal1[1].color = sf::Color(color);

    diagonal2[0].position = sf::Vector2f(position.x, position.y + size.y);
    diagonal2[0].color = sf::Color(color);
    diagonal2[1].position = sf::Vector2f(position.x + size.x, position.y);
    diagonal2[1].color = sf::Color(color);

    window.draw(diagonal1, 4, sf::Lines);
    window.draw(diagonal2, 4, sf::Lines);
}