#ifndef _cube_HPP
#define _cube_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class cube : public drawable {
public:

  cube( sf::Vector2f position, sf::Vector2f size );

	void draw( sf::RenderWindow & window ) override;

  sf::FloatRect getGlobalBounds();

  void setXHit();
  void setYHit();
  bool getXHit();
  bool getYHit();
  void clearHits();

  void move( sf::Vector2f delta );
  void jump( sf::Vector2f target );
  void jump( sf::Vector2i target );
  
private:
  sf::RectangleShape rect;
	sf::Vector2f position, size;
  bool xhit, yhit;
};

#endif
