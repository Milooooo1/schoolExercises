#ifndef _UI_HPP_
#define _UI_HPP_


namespace UI
{

    /*
    * This function draws info about the current game.
    * It doesn't take any parameters it communicates 
    * with the playfield module to get its data.
    * Returns 1 when the game should stop.
    * */
    char draw_info(void);

    /*
    * This function promts the user to do an action
    * It doesn't take any parameters, it returns 
    * as soon as the user has profided it with valid data.
    * It sends the data to the playfied module which processes it.
    * */
    void promt_user_action(void);

    /*
    * This function asks the user which direction to
    * move in. It asks the user for the room to move to
    * */
    void prompt_move(void);

    /*
    * This function asks the user which direction to
    * shoot in. It doesn't take any parameters
    * because it will prompt the user to provide it with data
    * */
    void prompt_shoot(void);

    /*
    * Asks at the beginning of the programm if you want 
    * to load the data from the config file.
    * */
    void prompt_load_config(void);

    /*
    * Asks at the end of the game if the player wants
    * to save the current game configuration for later
    * use. 
    * */
    void prompt_save_game(void);

    /*
    * Shows the leaderbord sorted by the highscore
    * */
    void prompt_leaderboard(void);

    /*
    * Asks the player to enter their username
    * */
    void prompt_username(void);

    /*
    * Sends the username to playfield.cpp
    * */
    void stats_to_playfield(void);

};

#endif // _UI_HPP_