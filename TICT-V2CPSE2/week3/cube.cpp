#include <SFML/Graphics.hpp>
#include "cube.hpp"

cube::cube( sf::Vector2f position, sf::Vector2f size, sf::Color color):
  position(position),
  size(size),
  color(color)
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

void cube::jump( sf::Vector2f target ){
	position = target;
}

void cube::jump( sf::Vector2i target ){
	jump( sf::Vector2f(
		static_cast< float >( target.x ),
		static_cast< float >( target.y )
	));
}
