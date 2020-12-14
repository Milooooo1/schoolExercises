#include <iostream>
#include "gameCore.hpp"
#include "textInterface.hpp"
#include "sfmlInterface.hpp"
#include "def.hpp"

int main( int argc, char *argv[] ){
	
	gameCore game = gameCore();
	textInterface TI = textInterface(game);
	sfmlInterface SI = sfmlInterface(game);

	char in;
	while(true){
		// clear();
		std::cout << "What interface would you like? G = GUI, T = Text, E = Exit\n Input: ";
		std::cin >> in;
		in = std::tolower(in);
		if(in == 'g'){
			SI.start();
		} else if (in == 't'){
			TI.start();
		} else if (in == 'e'){
			break;
		} else {
			std::cout << "Invalid input.\n";
		}
	}

	std::cout << "\nTerminating application\n";
	return 0;
}