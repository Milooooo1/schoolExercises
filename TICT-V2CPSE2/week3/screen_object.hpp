#ifndef _SCREEN_OBJECT_HPP
#define _SCREEN_OBJECT_HPP

#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <iostream>
#include "wall.hpp"
#include "cube.hpp"
#include "ball.hpp"
#include "image.hpp"
#include "drawable.hpp"
#include "exceptions.hpp"


class screen_object {
public:

    screen_object();

    screen_object(const screen_object&) = delete;

    static drawable * screen_object_read(std::ifstream & input_file);

    static void screen_object_write(drawable * objectToWrite, std::ostream & output_file);

private:


};

std::ifstream & operator>>( std::ifstream & input_file, sf::Vector2f & rhs);

std::ifstream & operator>>( std::ifstream & input_file, sf::Color & rhs);

#endif
