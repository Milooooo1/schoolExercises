#ifndef _naught_HPP
#define _naught_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class naught : public drawable {
public:

    naught( sf::Vector2f position, float size, sf::Color color = sf::Color::White );

	void draw( sf::RenderWindow & window ) override;
    
private:
    sf::Vector2f position;
    float size;
    sf::CircleShape circ;
    sf::Color color;
};

#endif
