#include <SFML/Graphics.hpp>
#include "image.hpp"

image::image( sf::Vector2f position, sf::Vector2f size, std::string filename ):
  drawable( position, sf::Color::White, "IMG", size ),
  filename( filename )
{
    if(!img.loadFromFile(filename, sf::IntRect(size.x, size.y, position.x, position.y))){
        throw error::invalid_image(filename);
    }
    sprite.setTexture(img);
    sprite.setTextureRect(sf::IntRect(size.x, size.y, position.x, position.y));
}

void image::draw( sf::RenderWindow & window ) {
    // img.setSmooth(true);
    sprite.setPosition(position);
    window.draw(sprite);
}

sf::FloatRect image::getGlobalBounds(){
  return sprite.getGlobalBounds();
}
