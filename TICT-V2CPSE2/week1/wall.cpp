#include <SFML/Graphics.hpp>
#include "wall.hpp"

wall::wall( sf::Vector2f position, sf::Vector2f size):
  position(position),
  size(size)
{}

void wall::draw( sf::RenderWindow & window ) {
  //sf::RectangleShape wall;
  rect.setSize(size);
  rect.setPosition(position);
  rect.setFillColor(sf::Color::Blue);
  window.draw(rect);
}

sf::FloatRect wall::getGlobalBounds(){
  return rect.getGlobalBounds();
}
