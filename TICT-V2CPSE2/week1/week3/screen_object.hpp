#ifndef _SCREEN_OBJECT_HPP
#define _SCREEN_OBJECT_HPP

#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <string> 
#include "wall.hpp"
#include "cube.hpp"
#include "ball.hpp"
#include "drawable.hpp"
#include "exceptions.hpp"

class screen_object {
public:
    
    screen_object();
    
    drawable * screen_object_read(std::ifstream & input_file);
    
    drawable * screen_object_write(std::ostream & output_file);
    
private:
    
};

std::ifstream & operator>>( std::ifstream & input_file, sf::Vector2f & rhs);

std::ifstream & operator>>( std::ifstream & input_file, sf::Color & rhs);

#endif