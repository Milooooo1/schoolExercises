#include <SFML/Graphics.hpp>
#include "grid.hpp"

grid::grid():
    drawable()
{}

void grid::draw( sf::RenderWindow & window ) {
    //Horizontal Line 1
    hLine1.setSize(sf::Vector2f(window.getSize().x, 10));
    hLine1.setPosition(sf::Vector2f(0, 153));
    hLine1.setFillColor(sf::Color::White);
    window.draw(hLine1);
    //Horizontal Line 2
    hLine2.setSize(sf::Vector2f(window.getSize().x, 10));
    hLine2.setPosition(sf::Vector2f(0, 316));
    hLine2.setFillColor(sf::Color::White);
    window.draw(hLine2);
    //Vertical Line 1
    vLine1.setSize(sf::Vector2f(10, window.getSize().y));
    vLine1.setPosition(sf::Vector2f(206, 0));
    vLine1.setFillColor(sf::Color::White);
    window.draw(vLine1);
    //Vertical Line 2
    vLine2.setSize(sf::Vector2f(10, window.getSize().y));
    vLine2.setPosition(sf::Vector2f(422, 0));
    vLine2.setFillColor(sf::Color::White);
    window.draw(vLine2);
}