#include "ui.hpp"
#include "messages.hpp"

#include "playfield.hpp"

#include <iostream>
#include <vector>


static int playfieldStatus;
static std::string playername = "default";


namespace UI
{
    void print_smell_info(void)
    {
        char currentSmell = playfield::smell();

        if((currentSmell & SMELL_WUMPUS) != 0)
            std::cout << SMELL_WUMPUS_MSG << std::endl;

        if((currentSmell & SMELL_BATS) != 0)
            std::cout << SMELL_BATS_MSG << std::endl;
    }


    char draw_info(void)
    {
        switch(playfieldStatus)
        {
            case PLAYFIELD_OK: break;
            case PLAYER_TELEPORTED: {std::cout << "The player has been teleported" << std::endl; break;}
            case PLAYFIELD_MISS: {std::cout << MISSED_MSG << std::endl; break;}
            case PLAYFIELD_NO_ARROWS: {std::cout << NO_ARROWS_MSG << std::endl; break;}
            case PLAYER_DIED: {std::cout << PLAYER_KILLED_MSG << std::endl; return 1;}
            case PLAYFIELD_HIT: {std::cout << PLAYER_WON_MSG << std::endl; return 1;}
            default: {std::cout << ERROR_MSG << std::endl; break;};
        }

        std::cout << CURRENT_ROOM_MSG << playfield::get_current_room() << std::endl;
        print_smell_info();

        playfield::Possibilities possible = playfield::get_possibilities();
        std::cout << POSSIBLE_DIRECTIONS_MSG << possible.a << " " << possible.b << " " << possible.c << std::endl;

        return 0;
    }


    void promt_user_action(void)
    {
        char choice;
        while(1)
        {
            std::cout << PROMPT_SHOOT_MOVE_MSG;
            std::cin >> choice;

            if(choice == 'S' || choice == 's')
                prompt_shoot();

            else if(choice == 'M' || choice == 'm')
                prompt_move();
            
            if( playfieldStatus >= PLAYFIELD_OK)
            {
                std::cout << std::endl;;
                break;
            }

            std::cout << INVALID_INPUT_MSG << std::endl;
        }
    }


    void prompt_move(void)
    {
        unsigned int choice;

        std::cout << PROMPT_ROOM_TO_MOVE_MSG;
        std::cin >> choice;

        playfieldStatus = playfield::move(choice);
    }

    
    void prompt_shoot(void)
    {
        unsigned int choice;

        std::cout << PROMPT_ROOM_TO_SHOOT_MSG;
        std::cin >> choice;

        playfieldStatus = playfield::shoot(choice);
    }

    void prompt_load_config(void)
    {
        char choice;
        std::cout << "Do you want to load a game? [y/n]" << std::endl;
        std::cin >> choice;
        if(choice == 'Y' || choice == 'y')
        {
            playfield::load_level();
            std::cout << "Loaded the configuration file." << std::endl;
        }
        else 
        {
            std::cout << "Automatic config selected." << std::endl;
        }
    }

    void prompt_save_game(void)
    {
        char choice;
        std::cout << "Do you want to save the game configuration? [y/n]" << std::endl;
        std::cin >> choice;
        if(choice == 'Y' || choice == 'y')
        {
            playfield::save_level();
            std::cout << "Game saved." << std::endl;
        }
        else
        {
            std::cout << "Current configuration not saved." << std::endl;
        }
        
    }

    void prompt_username(void)
    {
        std::cout << "Enter your username: ";
        std::cin >> playername;
    }

    void stats_to_playfield(void)
    {
        playfield::write_stats(playername);
    }

    void prompt_leaderboard(void)
    {
        char choice;
        unsigned int counter = 1;
        std::vector<std::string> statContents;
        std::cout << "Do you want to show the leaderbord [y/n]" << std::endl;
        std::cin >> choice;
        if(choice == 'Y' || choice == 'y')
        {
            std::cout << "The leaderbord" << std::endl;
            std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
            statContents = playfield::send_stats();
            for(unsigned int i = 0; i < statContents.size(); i+=3)
            {
                std::cout << "Number " << counter << " " << statContents[i] << " with a highscore of: " << statContents[i+1] << std::endl;
                counter++;
            }
        }
    }
}