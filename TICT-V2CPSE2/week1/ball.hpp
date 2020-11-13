#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class ball : public drawable	 {
public:

	ball( sf::Vector2f position, float size = 30.0 );

	void draw( sf::RenderWindow & window ) override ;

	//void move( sf::Vector2f delta );

	void setSpeed( sf::Vector2f delta );
	void move();

	void jump( sf::Vector2f target );
	void jump( sf::Vector2i target );

	sf::FloatRect getCurrentPosition();
	sf::FloatRect giveNextXPos();
	sf::FloatRect giveNextYPos();

	void changeXSpeed();
	void changeYSpeed();

	//void changeDirection( sf::Vector2f direction );
private:
	sf::CircleShape circle;
	sf::Vector2f position, speed;
	float size;
};

#endif
