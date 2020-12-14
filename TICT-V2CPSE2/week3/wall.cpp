#include <SFML/Graphics.hpp>
#include "wall.hpp"

wall::wall( sf::Vector2f position, sf::Vector2f size, sf::Color color):
  drawable(position, color, "WALL", size)
{}

void wall::draw( sf::RenderWindow & window ) {
  rect.setSize(size);
  rect.setPosition(position);
  rect.setFillColor(color);
  window.draw(rect);
}

sf::FloatRect wall::getGlobalBounds(){
  return rect.getGlobalBounds();
}
