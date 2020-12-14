#include <SFML/Graphics.hpp>
#include "naught.hpp"

naught::naught( sf::Vector2f position, float size, sf::Color color):
    drawable(),
    position(position),
    size(size),
    color(color)
{}

void naught::draw( sf::RenderWindow & window ) {
    circ.setRadius(size);
    circ.setPosition(position);
    circ.setFillColor(sf::Color::Transparent);
    circ.setOutlineThickness(10);
    circ.setOutlineColor(color);
    window.draw(circ);
}