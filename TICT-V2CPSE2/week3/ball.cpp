#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include <iostream>

ball::ball( sf::Vector2f position, sf::Color color , float size) :
	drawable( position, color, "BALL", sf::Vector2f(size, 0.0)),
	radius{ size }
{}

void ball::draw( sf::RenderWindow & window ) {
	circle.setRadius(radius);
	circle.setPosition(position);
	circle.setFillColor(color);
	window.draw(circle);
}

void ball::setSpeed( sf::Vector2f delta ){
	speed = delta;
}

void ball::move(){
	position += speed;
}

sf::FloatRect ball::getCurrentPosition(){
	sf::FloatRect nextPos = circle.getGlobalBounds();
	nextPos.left += speed.x;
	nextPos.top += speed.y;
	return nextPos;
}

sf::FloatRect ball::giveNextXPos(){
	sf::FloatRect nextPos = circle.getGlobalBounds();
	nextPos.left += speed.x;
	return nextPos;
}

sf::FloatRect ball::giveNextYPos(){
	sf::FloatRect nextPos = circle.getGlobalBounds();
	nextPos.top += speed.y;
	return nextPos;
}

void ball::changeXSpeed(){
	speed.x *= -1;
}

void ball::changeYSpeed(){
	speed.y *= -1;
}

sf::FloatRect ball::getGlobalBounds(){
  return circle.getGlobalBounds();
}
