#include "screen_object.hpp"


screen_object::screen_object(){}; //Private constructor

drawable * screen_object::screen_object_read(std::ifstream & input_file){
    sf::Vector2f position, size;
    sf::Color SFML_color;
    std::string type, color, filename;
    input_file >> position >> type >> color;

    // std::cout << "Received " << type << " with Position: {" << position.x << "," <<  position.y << "} and color "<< color << ".\n";

    if(type == "WALL"){
        if(color == "blue"){
            input_file >> size;
            SFML_color = sf::Color::Blue;
            return new wall(position, size, SFML_color);
        } else {
            input_file >> size;
            SFML_color = sf::Color::White; //Default color
            return new wall(position, size, SFML_color);
        }
    } else if(type == "BALL"){
        float radius;
        if(color == "cyan"){
            input_file >> radius;
            SFML_color = sf::Color::Cyan;
            return new ball(position, SFML_color, radius);
        } else if(color == "blue") {
            input_file >> radius;
            SFML_color = sf::Color::Blue;
            return new ball(position, SFML_color, radius);
        } else {
            SFML_color = sf::Color::White; //Default color
            return new ball(position, SFML_color, radius);
        }
    } else if(type == "CUBE"){
        if(color == "magenta"){
            input_file >> size;
            SFML_color = sf::Color::Magenta;
            return new cube(position, size, SFML_color);
        } else {
            input_file >> size;
            SFML_color = sf::Color::White;  //Default color
            return new cube(position, size, SFML_color);
        }
    } else if (type == "IMG") {
        filename = color;
        input_file >> size;
        return new image(position, size, filename);
    } else {
        throw error::invalid_type( type );
        return nullptr;
    }
}

void screen_object::screen_object_write(drawable * objectToWrite, std::ostream & output_file){

    sf::Vector2f position = objectToWrite->getPosition();
    sf::Vector2f size = objectToWrite->getSize();
    std::string type = objectToWrite->getType();
    sf::Color sfColor = objectToWrite->getColor();
    std::string strColor;

    const struct{sf::Color color; const char * name; } colors[]{
        {  sf::Color::Yellow,   "yellow"  },
        {  sf::Color::Red,      "red"     },
        {  sf::Color::Cyan,     "cyan"    },
        {  sf::Color::Magenta,  "magenta" },
        {  sf::Color::Blue,     "blue"    },
        {  sf::Color::Green,    "green"   },
        {  sf::Color::Black,    "black"   },
        {  sf::Color::White,    "white"   }
    };

    for(auto const & color : colors ){
        if(color.color == sfColor){
            strColor = color.name;
        }
    }

    if(type == "IMG"){
        output_file << "(" << position.x << "," << position.y << ") " << type << " ball-photo.png" << " (" << size.x << "," << size.y << ")\n";
    } else if(type == "BALL"){
        output_file << "(" << position.x << "," << position.y << ") " << type << " " << strColor << " " << size.x << "\n";
    } else {
        output_file << "(" << position.x << "," << position.y << ") " << type << " " << strColor << " (" << size.x << "," << size.y << ")\n";
    }
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
        { "yellow",     sf::Color::Yellow   },
        { "red",        sf::Color::Red      },
        { "cyan",       sf::Color::Cyan     },
        { "magenta",    sf::Color::Magenta  },
        { "blue",       sf::Color::Blue     },
        { "green",      sf::Color::Green    },
        { "black",      sf::Color::Black    },
        { "white",      sf::Color::White    }
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
