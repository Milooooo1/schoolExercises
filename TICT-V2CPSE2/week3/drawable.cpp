#include "drawable.hpp"

drawable::drawable(sf::Vector2f position, sf::Color color, std::string name, sf::Vector2f size):
	position(position),
	color(color),
	name(name),
	size(size)
{}

void drawable::jump( sf::Vector2f target ){
	position = target;
}

void drawable::jump( sf::Vector2i target ){
	jump( sf::Vector2f(
		static_cast< float >( target.x ),
		static_cast< float >( target.y )
	));
}

sf::Vector2f drawable::getPosition(){
	return position;
}

sf::Color drawable::getColor(){
	return color;
}

std::string drawable::getType(){
	return name;
}

sf::Vector2f drawable::getSize(){
	return size;
}
