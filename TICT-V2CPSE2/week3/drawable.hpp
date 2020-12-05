#ifndef _drawable_HPP
#define _drawable_HPP

#include <SFML/Graphics.hpp>

class drawable {
public:

  drawable();

	virtual void draw( sf::RenderWindow & window ) = 0;

private:
	sf::Vector2f position, size;
};

#endif
