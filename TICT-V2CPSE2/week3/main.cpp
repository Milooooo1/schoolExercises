#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <array>
#include "ball.hpp"
#include "wall.hpp"
#include "drawable.hpp"
#include "cube.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
	   std::function< bool() > condition,
	   std::function< void() > work
	) : condition( condition ),
		work( work )
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
		),
		work(work)
	{}

	action(
		bool mov,
		std::function< void() > work
	) :
		condition(
			[ mov ]()->bool { return true; }
		),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main( int argc, char *argv[] ){
	std::cout << "Starting application 03-08 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	ball my_ball{ sf::Vector2f{ 320.0, 240.0 }, sf::Color::Cyan };
	wall northWall = wall(
		sf::Vector2f(10, 10),						//position
		sf::Vector2f( window.getSize().x - 20 , 10), //size
		sf::Color::Blue
	);
	wall westWall  = wall(
		sf::Vector2f(window.getSize().x - 20, 10),	//position
		sf::Vector2f( 10 , window.getSize().y - 20), //size
		sf::Color::Blue
	);
	wall southWall = wall(
		sf::Vector2f( 10, window.getSize().y - 20), //position
		sf::Vector2f( window.getSize().x - 20 , 10),//size
		sf::Color::Blue
	);
	wall eastWall  = wall(
		sf::Vector2f(10, 10),						//position
		sf::Vector2f( 10, window.getSize().y - 20), //size
		sf::Color::Blue
	);
	cube midpoint  = cube(
		sf::Vector2f( (window.getSize().x - 20) / 2, (window.getSize().y -20) / 2),
		sf::Vector2f( 40, 40),
		sf::Color::Magenta
	);

	std::array< drawable *, 6 > objects = {
		&northWall, &westWall, &southWall, &eastWall, &midpoint, &my_ball
	};
	action actions[] = {
		action( sf::Keyboard::Left,  [&](){ midpoint.move( sf::Vector2f( -1.0,  0.0 )); }),
		action( sf::Keyboard::Right, [&](){ midpoint.move( sf::Vector2f( +1.0,  0.0 )); }),
		action( sf::Keyboard::Up,    [&](){ midpoint.move( sf::Vector2f(  0.0, -1.0 )); }),
		action( sf::Keyboard::Down,  [&](){ midpoint.move( sf::Vector2f(  0.0, +1.0 )); }),
		action( sf::Mouse::Left,     [&](){ midpoint.jump( sf::Mouse::getPosition( window )); }),
		action( true,								 [&](){ my_ball.move( /*sf::Vector2f( +2.0, +2.0 ));*/ );}),
		action( [&](){ return southWall.getGlobalBounds().intersects(my_ball.getCurrentPosition()); },
		 				[&](){ my_ball.changeYSpeed(); }),
		action( [&](){ return eastWall.getGlobalBounds().intersects(my_ball.getCurrentPosition());  },
		 				[&](){ my_ball.changeXSpeed(); }),
		action( [&](){ return northWall.getGlobalBounds().intersects(my_ball.getCurrentPosition()); },
		 				[&](){ my_ball.changeYSpeed(); }),
		action( [&](){ return westWall.getGlobalBounds().intersects(my_ball.getCurrentPosition());  },
		 				[&](){ my_ball.changeXSpeed(); }),
		action( [&](){ if(midpoint.getGlobalBounds().intersects(my_ball.giveNextXPos())){
						     		midpoint.setXHit();
					       } else if(midpoint.getGlobalBounds().intersects(my_ball.giveNextYPos())) {
									 	midpoint.setYHit();
					 			 }
					    		  return midpoint.getGlobalBounds().intersects(my_ball.getCurrentPosition()); },
		 				[&](){ if(midpoint.getXHit()) { 
					    			my_ball.changeXSpeed(); my_ball.move(); midpoint.clearHits();  
					 			 } else if(midpoint.getYHit()) {
									 	my_ball.changeYSpeed(); my_ball.move(); midpoint.clearHits(); 
					 			 } })
		};

	my_ball.setSpeed( sf::Vector2f( +2.0, +2.0) );
	while (window.isOpen()) {
		for( auto & action : actions ){
			action();
		}

		window.clear();

		for( auto & i : objects){
			i->draw( window );
		}
		window.display();

		sf::sleep( sf::milliseconds( 20 ));

      sf::Event event;
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
	} // end of while

	std::cout << "Terminating application\n";
	return 0;
}
