#ifndef _image_HPP
#define _image_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "exceptions.hpp"

class image : public drawable {
public:

    image( sf::Vector2f position, sf::Vector2f size, std::string filename);

    void draw( sf::RenderWindow & window ) override;

    sf::FloatRect getGlobalBounds();


private:
    std::string filename;
    sf::Texture img;
    sf::Sprite sprite;
};

#endif
