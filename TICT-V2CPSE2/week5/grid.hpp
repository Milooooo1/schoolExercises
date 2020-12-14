#ifndef _grid_HPP
#define _grid_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class grid : public drawable {
public:

    grid();

	void draw( sf::RenderWindow & window ) override;
    
private:
    sf::RectangleShape hLine1, hLine2, vLine1, vLine2;
    sf::Color color;
};

#endif
