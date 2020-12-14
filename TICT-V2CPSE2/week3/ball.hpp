#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class ball : public drawable	 {
public:

	ball( sf::Vector2f position, sf::Color color = sf::Color::Cyan, float size = 30.0);

	void draw( sf::RenderWindow & window ) override ;

	sf::FloatRect getGlobalBounds() override ;

	void setSpeed( sf::Vector2f delta );
	void move();

	sf::FloatRect getCurrentPosition();
	sf::FloatRect giveNextXPos();
	sf::FloatRect giveNextYPos();

	void changeXSpeed();
	void changeYSpeed();

private:
	sf::CircleShape circle;
	sf::Vector2f speed;
	float radius;
};

#endif
