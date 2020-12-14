#include "screen_object.hpp"


screen_object::screen_object(){};

drawable * screen_object::screen_object_read(std::ifstream & input_file){
    sf::Vector2f position, size;
    sf::Color SFML_color;
    std::string type, color;
    input_file >> position >> type >> color;
    
    
    if(type == "RECTANGLE"){
        if(color == "blue"){
            input_file >> size;
            SFML_color = sf::Color::Blue;
            return new wall(position, size, SFML_color);
        } else {
            return new wall(position, size); //Call object with default color paramter
        }
    } else if(type == "BALL"){
        float radius;
        if(color == "cyan"){
            input_file >> radius;
            SFML_color = sf::Color::Cyan;
            return new ball(position, SFML_color, radius);
        } else {
            return nullptr;
        }
    } else if(type == "CUBE"){
        if(color == "magenta"){
            input_file >> size;
            SFML_color = sf::Color::Magenta;
            return new cube(position, size, SFML_color);
        } else {
            return new cube(position, size); //Call object with default color paramter
        }
    } else {
        return nullptr;
    }
}

drawable * screen_object::screen_object_write(std::ostream & output_file){
    return nullptr;
}

std::ifstream & operator>>( std::ifstream & input_file, sf::Vector2f & rhs){
    char c;
    if( ! (input_file >> c)){       throw error::end_of_file(); }
    if( c != '('){                  throw error::invalid_position( c ); }
    if( ! (input_file >> rhs.x )){  throw error::invalid_position( c ); }
    if( ! (input_file >> c )){      throw error::invalid_position( c ); }
    if( ! (input_file >> rhs.y )){  throw error::invalid_position( c ); }
    if( ! (input_file >> c )){      throw error::invalid_position( c ); }
    if( c != ')'){                  throw error::invalid_position( c ); }
    
    return input_file;
}

std::ifstream & operator>>( std::ifstream & input_file, sf::Color & rhs){
    std::string s;
    input_file >> s;
    const struct{ const char * name; sf::Color color; } colors[]{
        { "yellow", sf::Color::Yellow },
        { "red", sf::Color::Red },
        { "cyan", sf::Color::Cyan },
        { "magenta", sf::Color::Magenta },
        { "blue", sf::Color::Blue },
        { "green", sf::Color::Green },
        { "black", sf::Color::Black },
        { "white", sf::Color::White }
    };
    for(auto const & color : colors ){
        if(color.name == s){
            rhs = color.color;
            return input_file;
        }
    }
    if( s == ""){
        throw error::end_of_file();
    } else {
        throw error::unknown_color( s );
    }
}