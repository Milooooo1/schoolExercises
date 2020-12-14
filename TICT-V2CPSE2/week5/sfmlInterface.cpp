#include "sfmlInterface.hpp"


sfmlInterface::sfmlInterface(gameCore _game):
    game(_game)
{}

void sfmlInterface::mainLoop(){
    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "Naughts and Crosses" };

    auto _grid = grid();

    auto tl = button(sf::Vector2f(0,0),            std::array<int, 2>{0, 0});
    auto tm = button(sf::Vector2f(216, 0),         std::array<int, 2>{0, 1});
    auto tr = button(sf::Vector2f(432, 0),         std::array<int, 2>{0, 2});
    auto ml = button(sf::Vector2f(0, 163),         std::array<int, 2>{1, 0});
    auto mm = button(sf::Vector2f(216, 163),       std::array<int, 2>{1, 1});
    auto mr = button(sf::Vector2f(432, 163),       std::array<int, 2>{1, 2});
    auto bl = button(sf::Vector2f(0, 326),         std::array<int, 2>{2, 0});
    auto bm = button(sf::Vector2f(216, 326),       std::array<int, 2>{2, 1});
    auto br = button(sf::Vector2f(432, 326),       std::array<int, 2>{2, 2});

    std::array<button *, 9> buttons = { &tl, &tm, &tr, &ml, &mm, &mr, &bl, &bm, &br };

    while(window.isOpen()){

        window.clear();
        _grid.draw(window);

        //Check for all buttons if they are pressed
        for(auto & button : buttons){
            button->draw(window);
            if( button->getGlobalBounds().contains( sf::Vector2f( sf::Mouse::getPosition(window) ) ) && sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
                sf::sleep(sf::milliseconds(50));
                if(button->isPressed == true){
                    continue;
                }
                button->setButtonPressed(true, (ply % 2) + 1);
                game.play(button->getBoardPosition());
                int res = game.checkWin();
                if(res != 0){
                    if(res == 3){ //Tie
                        winner = res;  
                        finished = true;

                    } else {      //Won
                        winner = res;
                        finished = true;
                    }
                }
                ply++;
            } else if ( button->getGlobalBounds().contains( sf::Vector2f( sf::Mouse::getPosition(window) ) ) && sf::Mouse::isButtonPressed(sf::Mouse::Right) ){
                sf::sleep(sf::milliseconds(50));
                button->clearPress();
                game.undoLastMove();
                ply--;
            }
        }

        //Draw shape for each button that has been pressed. 
        for(auto & button : buttons){
            if ( button->isPressed ){
                if ( button->pressedByPlayer == 2 ){
                    auto _naught = naught(sf::Vector2f(button->getCoords().x + 20, button->getCoords().y), 60);
                    _naught.draw(window);
                } else {
                    auto _cross = cross(button->getCoords());
                    _cross.draw(window);
                }
            }
        } 



        window.display();

        //Check if the game has ended
        if( finished ){
            for(auto & button : buttons){
                button->clearPress();
            }

            endScreen(window);
        }

        //Respond to exit
        sf::Event event;
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
    } // end of while
}

void sfmlInterface::start(){
    std::cout << "Game starting...\n";
    ply = 0; 
    winner = 0;
    finished = false;
    game.reset();
    mainLoop();
}

void sfmlInterface::endScreen(sf::RenderWindow & window){
    // std::cout << "We're here: " << __LINE__ << std::endl;
    window.clear();
    
    sf::RectangleShape rematchButton;
    rematchButton.setPosition(sf::Vector2f(window.getSize().x / 2 - 60, 300));
    rematchButton.setSize(sf::Vector2f(100, 40));
    rematchButton.setFillColor(sf::Color::White);
    
    sf::Font font;
    font.loadFromFile("rajdhani.ttf");

    sf::Text endscreen;
    endscreen.setFont(font);
    if(winner == 3){
        endscreen.setString("The game ended in a tie!");
    } else if (winner == 2){
        endscreen.setString("Player 2 won the game!");
    } else if (winner == 1){
        endscreen.setString("Player 1 won the game!");
    }

    endscreen.setPosition(sf::Vector2f((window.getSize().x / 2) - 200, 40));
    endscreen.setCharacterSize(40);
    endscreen.setFillColor(sf::Color::White);

    sf::Text rematchText("Rematch", font);
    rematchText.setPosition(sf::Vector2f(window.getSize().x / 2 - 55, 305));
    rematchText.setCharacterSize(25);
    rematchText.setFillColor(sf::Color::Black);
    
    window.draw(rematchButton);
    window.draw(rematchText);
    window.draw(endscreen);

    window.display();
        
    while(true){
        if(rematchButton.getGlobalBounds().contains( sf::Vector2f( sf::Mouse::getPosition(window) ) ) && sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
            ply = 0; 
            winner = 0;
            finished = false;
            game.reset();
            sf::sleep(sf::milliseconds(80));
            return;
        }  

        sf::Event event;
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		} 
    }
}
