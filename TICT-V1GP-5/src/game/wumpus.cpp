#include "wumpus.hpp" 

#include <iostream>


int main(void)
{
    playfield::init(20);
    UI::prompt_username();
    UI::prompt_load_config();

    while(1)
    {
        if(UI::draw_info())
            break;

        UI::promt_user_action();
    };

    UI::prompt_save_game();
    UI::prompt_leaderboard();
    UI::stats_to_playfield();

    playfield::cleanup();
    return 0;
}