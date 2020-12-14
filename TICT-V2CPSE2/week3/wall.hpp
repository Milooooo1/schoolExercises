#ifndef _wall_HPP
#define _wall_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class wall : public drawable {
public:

  wall( sf::Vector2f position, sf::Vector2f size, sf::Color color= sf::Color::Blue );

	void draw( sf::RenderWindow & window ) override;

    sf::FloatRect getGlobalBounds();


private:
    sf::RectangleShape rect;
};

#endif
