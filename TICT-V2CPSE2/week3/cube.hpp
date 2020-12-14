#ifndef _cube_HPP
#define _cube_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class cube : public drawable {
public:

  cube( sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color::Magenta );

  void draw( sf::RenderWindow & window ) override;

  sf::FloatRect getGlobalBounds() override ;

  void setXHit();
  void setYHit();
  bool getXHit();
  bool getYHit();
  void clearHits();

  void move( sf::Vector2f delta );


private:
  sf::RectangleShape rect;
  bool xhit, yhit;
};

#endif
