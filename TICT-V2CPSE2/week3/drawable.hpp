#ifndef _drawable_HPP
#define _drawable_HPP

#include <SFML/Graphics.hpp>
#include <string>

class drawable {
public:

 	drawable(sf::Vector2f position, sf::Color color, std::string name, sf::Vector2f size);

	virtual void draw( sf::RenderWindow & window ) = 0;

	virtual sf::FloatRect getGlobalBounds() = 0;

	void jump( sf::Vector2f target );

	void jump( sf::Vector2i target );

    sf::Vector2f getPosition();

    sf::Color getColor();

    std::string getType();

    sf::Vector2f getSize();

protected:
	sf::Vector2f position;
    sf::Color color;
    std::string name;
    sf::Vector2f size;
};

#endif
