#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include <iostream>

ball::ball( sf::Vector2f position, float size ) :
	position{ position },
	size{ size }
{}

void ball::draw( sf::RenderWindow & window ) {
	// sf::CircleShape circle;
	circle.setRadius(size);
	circle.setPosition(position);
	circle.setFillColor(sf::Color::Cyan);
	window.draw(circle);
}

// void ball::move( sf::Vector2f delta ){
// 	position += delta;
// }

void ball::setSpeed( sf::Vector2f delta ){
	speed = delta;
}

void ball::move(){
	position += speed;
}

void ball::jump( sf::Vector2f target ){
	position = target;
}

void ball::jump( sf::Vector2i target ){
	jump( sf::Vector2f(
		static_cast< float >( target.x ),
		static_cast< float >( target.y )
	));
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
