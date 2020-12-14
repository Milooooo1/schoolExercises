#include <SFML/Graphics.hpp>
#include "cube.hpp"

cube::cube( sf::Vector2f position, sf::Vector2f size, sf::Color color):
  drawable(position, color, "CUBE", size)
{}

void cube::draw( sf::RenderWindow & window ) {
  rect.setSize(size);
  rect.setPosition(position);
  rect.setFillColor(color);
  window.draw(rect);
}

sf::FloatRect cube::getGlobalBounds(){
  return rect.getGlobalBounds();
}

void cube::setXHit(){
  xhit = true;
}

void cube::setYHit(){
  yhit = true;
}

bool cube::getXHit(){
  return xhit;
}

bool cube::getYHit(){
  return yhit;
}

void cube::clearHits(){
  xhit = false;
  yhit = false;
}

void cube::move( sf::Vector2f delta ){
	position += delta;
}
