#include <iostream>
#include <fstream>
#include <ostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "ball.hpp"
#include "wall.hpp"
#include "drawable.hpp"
#include "cube.hpp"
#include "exceptions.hpp"
#include "screen_object.hpp"

int main( int argc, char *argv[] ){
	std::cout << "Starting huiswerk opdracht week 3 Milo Beliën\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	screen_object factory;
	std::vector<drawable * > objectList;
	std::ifstream input("objects.txt");
	// bool saveFile = true;

	//Load all objects from fule in objectList
	try {
		for(;;){
			objectList.push_back(factory.screen_object_read(input));
			// std::cout << "Object received.\n"; //This cout shows it does get all the objects.
		}
	} catch (error::end_of_file()){
		//Do nothing
	} catch (error::syntax_error & problem) {
		std::cout << problem.what();
		// std::cout << "We're "<< __LINE__<<"\n";
		return 0;
	} catch (std::exception & problem){
		std::cout << "Unexpected error.\n";
		std::cout << problem.what();
	}

	//Main loop, checks if the objects need to be moved and draws them if needed.
	while (window.isOpen()) {

		//Select an object to move and move it.
		for( auto & object : objectList){
			if(
				object->getGlobalBounds().contains( sf::Vector2f( sf::Mouse::getPosition(window) ) )
				&& sf::Mouse::isButtonPressed( sf::Mouse::Left)
			  )
			{
				sf::sleep(sf::milliseconds(50));
				while(true){
					if(sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
						object->jump( sf::Mouse::getPosition(window));
						sf::sleep(sf::milliseconds(50));
						break;
					}
				}
			}
		}

		window.clear();

		//Draw all objects on screen and write new locations to file.
		std::ofstream file("objects.txt");
		for( auto & object : objectList){
			object->draw( window );
		}

		window.display();

		sf::sleep( sf::milliseconds( 20 ));
      	sf::Event event;
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				//Write objects to file when done with the application

				// if(saveFile){
					std::ofstream file("objects.txt");
					for( auto & object : objectList){
						screen_object::screen_object_write(object, file);
					}
				// }

				window.close();
			}
		}
	} // end of while

	std::cout << "Terminating application\n";
	return 0;
}
