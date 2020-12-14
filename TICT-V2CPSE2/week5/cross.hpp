#ifndef _cross_HPP
#define _cross_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class cross : public drawable {
public:

    cross( sf::Vector2f position, sf::Vector2f size = sf::Vector2f(166, 113), sf::Color color= sf::Color::White );

	void draw( sf::RenderWindow & window ) override;
    
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vertex diagonal1[2], diagonal2[2];
    sf::Color color;
};

#endif
