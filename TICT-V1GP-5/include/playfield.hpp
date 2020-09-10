#ifndef _PLAYFIELD_HPP_
#define _PLAYFIELD_HPP_


#define SHUFFLE_NUMBER_OF_PASSES 32

#include <vector>
#include <string>

// Enum to make the life of the compiler that much easier.
enum PLAYFIELD_ERROR_CODES 
{
    PLAYFIELD_OK = 0,
    PLAYFIELD_FIELD_DOES_NOT_EXIST = -1,
    PLAYFIELD_ACTION_NOT_POSSIBLE = -2,
    PLAYFIELD_HIT = 1,
    PLAYFIELD_MISS = 2,
    PLAYER_DIED = 3,
    PLAYFIELD_NO_ARROWS = 4,
    PLAYER_TELEPORTED = 5
};


enum SMELLS
{
    SMELL_WUMPUS = 0x1,
    SMELL_BATS = 0x2
};


namespace playfield
{
    // OBJECTS
    /*
    * This struct contains three unsigned int representing
    * the rooms a player can move to.
    * */
    struct Possibilities 
    {
        unsigned int a;
        unsigned int b;
        unsigned int c;

        unsigned int operator[](int index);
    };

    // FUNCTIONS
    /*
    * Initialises the playfield
    * must be called before any other
    * functions of this module is called.
    * Parameters:
    *   uint size   size of the playfield
    * */
    void init(unsigned int size);
    
    /*
    * Loads all the variables
    * from the config file into
    * the local variables
    */
    void load_level();

    /*
    * Saves all the variables
    * from the current game to
    * the config file
    * */
    void save_level();

    /*
    * Saves the struct of all the 
    * statistics to a text file
    * */
    void write_stats(std::string);

    /*
    * Reads all the data from the file
    * into a struct. 
    * */
    void load_stats();
    
    /*
    * Sends stats to UI
    * */
    std::vector<std::string> send_stats();

    /*
    * Cleans up dynamically allocated
    * Resources.
    * */
    void cleanup(void);

    /*
    * Returns the room the player is currently in.
    * */
    unsigned int get_current_room(void);

    /*
    * Returns a structure containing the three
    * rooms the player can move to.
    * */
    Possibilities get_possibilities(void);

    /*
    * Moves the player into a new room
    * Returns PLAYFIELD_OK or error
    * */
    int move(unsigned int roomToMoveTo);

    /*
    * Returns objects the player can currently
    * smell.
    * */
    char smell(void);

    /*
    * Player shoots to an adjacent room
    * Returns 1 upon hitting wumpus
    * Zero when missing
    * or error code
    *  */
    int shoot(unsigned int room);

};

#endif //_PLAYFIELD_HPP_