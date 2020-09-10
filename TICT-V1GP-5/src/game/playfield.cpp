#include "playfield.hpp"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

static char* roomLookupTable;
static unsigned int playfieldSize;
static unsigned int actualPlayfieldSize;
static unsigned int currentRoom;
static unsigned int numberOfArrows;
static unsigned int numberOfBats;
static unsigned int numberOfPits;
static unsigned int wumpusRoom;
static unsigned int *bats;
static std::vector<int> map, batLocations, holeLocations = {};
static playfield::Possibilities possibleMoves;
static std::vector<std::string> statContents = {};
static int amountOfMoves = 0;

static int move_player_random(void);

// static helper functions
static inline void shuffle_lookup_table(void)
{
    // Get random indexes
    int indexA = rand() % playfieldSize;
    int indexB = rand() % playfieldSize;
    char tmp;

    // Swap two values
    tmp = roomLookupTable[indexA];
    roomLookupTable[indexA] = roomLookupTable[indexB];
    roomLookupTable[indexB] = tmp;
}

static void randomise_map(void)
{
    // Generates the initial values, an ordered list
    for(unsigned int i = 0; i <= actualPlayfieldSize; i++)
    {
        roomLookupTable[i] = i+1;
    }

    // randomises/shuffles the map 
    for(int i = SHUFFLE_NUMBER_OF_PASSES; i > 0; i--)
    {
        shuffle_lookup_table();
    } 
}

static inline bool item_in_array(unsigned int roomToSearch, unsigned int *arrayToSearch, unsigned int arraySize)
{
    for(unsigned i = 0; i < arraySize; i++ )
    {
        if(roomToSearch == arrayToSearch[i])
        {
           return true;
        }
    }
    return false;
}

static void spawn_wumpus_at_random(void)
{
    // Player spawns at 0 so We'll use a number between 1 and playfieldsize
    wumpusRoom = (rand() % actualPlayfieldSize) + 1;
}

static void spawn_bats_at_random(void)
{   
    bats = new unsigned int [numberOfBats];
    // spawns bats equal to numberOfBats
    for(unsigned int i = 0; i < numberOfBats; i++)
    {
        bats[i] = (rand() % actualPlayfieldSize) + 1;
        while(bats[i] == wumpusRoom)
        {
            bats[i] = (rand() % actualPlayfieldSize) + 1;
        }
    }
}

static inline unsigned int room_on_left(const unsigned int& origin)
{
    if(origin == 0)
        return roomLookupTable[actualPlayfieldSize];

    return roomLookupTable[(origin - 1)];
} 

static inline unsigned int room_across(const unsigned int& origin)
{
    if(origin >= (playfieldSize >> 1))
        return roomLookupTable[(origin - (playfieldSize >> 1))];

    return roomLookupTable[(origin + (playfieldSize >> 1))];
}

static inline unsigned int room_on_right(const unsigned int& origin)
{
    if(origin == actualPlayfieldSize)
        return roomLookupTable[0];

    return roomLookupTable[(origin + 1)];
}

static void calculate_possibilities(playfield::Possibilities& poss, const unsigned int& origin)
{
    poss.a = room_on_left(origin);
    poss.b = room_across(origin);
    poss.c = room_on_right(origin);
}


static inline bool valid_direction(unsigned int room)
{
    return ((room == possibleMoves.a) || (room == possibleMoves.b) || (room == possibleMoves.c)) != 0;
}

// Searches the lookupTable for the index of a certain room
static inline int room_to_index(unsigned int room)
{
    for(unsigned int i = 0; i <= actualPlayfieldSize; i++)
    {
        if((unsigned int)roomLookupTable[i] == room)
            return i;
    }

    return -1;
}

static inline int playfield_reaction(void)
{
    if(currentRoom == wumpusRoom)
        return PLAYER_DIED;
    
    if(item_in_array(currentRoom, bats, numberOfBats))
    {
        move_player_random(); 
        return PLAYER_TELEPORTED;
    }
    
    return PLAYFIELD_OK;
}

static int move_player_random(void)
{   
    playfield::move((rand() % actualPlayfieldSize)+1);

    return PLAYER_TELEPORTED;
}


// This is somewhat poorly written could be improved.
// Places INDEXES in array not room numbers.
static void get_reachable_two_moves(unsigned int *arrayToSaveTo)
{
    playfield::Possibilities reachable[4];

    calculate_possibilities(reachable[0], currentRoom);
    calculate_possibilities(reachable[1], room_to_index(reachable[0][0]));
    calculate_possibilities(reachable[2], room_to_index(reachable[0][1]));
    calculate_possibilities(reachable[3], room_to_index(reachable[0][2]));

    //Dump ints
    for(int i = 0; i < 4; i++)
    {
        //std::cout << "-->";
        for(int j = 0; j < 3; j++)
        {
            arrayToSaveTo[((i*3)+j)] = room_to_index(reachable[i][j]);
            //std::cout << reachable[i][j] << std::endl;
        }
    }
}


// Functions that will be accessible to other parts of program
namespace playfield 
{
    // Write [] operator for struct for easy access.
    unsigned int Possibilities::operator[](int index)
    {
        switch(index)
        {
            case 0: return a;
            case 1: return b;
            case 2: return c;
            default: return 0;
        }
    }


    void init(unsigned int size)
    {
        roomLookupTable = new char[size];
        numberOfArrows = 5;
        numberOfBats = 5;
        playfieldSize = size;
        actualPlayfieldSize = size-1; // actualPlayfieldSize will be used to acces members of array(that start at zero)
        
        // A lot of called functions depend on rand()
        srand((unsigned int)time(NULL));
        randomise_map();

        currentRoom = 0;
        calculate_possibilities(possibleMoves, currentRoom);

        spawn_wumpus_at_random();
        spawn_bats_at_random();
        load_stats();
    } 

    void load_level()
    {
        unsigned int numberOfLines = 0;
        std::string line;
        std::string count;
        std::ifstream config;                                           //ifstream so file is opened as read only.
        config.open("config.txt");
        if(config.is_open())
        {
            while(!config.eof())                                        //counts the lines in config.txt            
            {
                getline(config, count);
                numberOfLines++;
            }
            config.clear();
            config.seekg(0);                                            //goes back to the beginning of the file
            for(unsigned int i = 0; i < numberOfLines; i++){
                getline(config, line);
                if(i == 0 && line == "1"){                              //checks if automatic config is enabled.
                    config.close();
                    break;
                }
                else if(i == 0)
                {
                    continue;
                }
                else if(i == 1)                                         //Saves the playfieldsize
                {  
                    playfieldSize = std::atoi(line.c_str());
                    actualPlayfieldSize = playfieldSize - 1;
                    roomLookupTable = new char[playfieldSize];
                }
                else if (i < ( 2 + playfieldSize))                      //Goes through all the rooms and saves them in an array
                {
                    roomLookupTable[i - 2] = std::atoi(line.c_str());
                }
                else if (i == (2 + playfieldSize))                      //Saves the number of bats
                {
                    numberOfBats = std::atoi(line.c_str());
                }
                else if (i < (playfieldSize + numberOfBats + 3))        //Goes through all the bats and saves them in a vector
                {
                    batLocations.push_back(std::atoi(line.c_str()));
                }
                else if (i == (playfieldSize + numberOfBats + 3))       //Saves the number of pits
                {
                    numberOfPits = std::atoi(line.c_str());
                }
                else if (i < (playfieldSize + numberOfBats + numberOfPits + 4)) //Goes through all the pits and saves them in a vector
                {
                    holeLocations.push_back(std::atoi(line.c_str()));
                }
                else if (i == numberOfLines - 1)                        //Saves the wumpus room
                {   
                    wumpusRoom = std::atoi(line.c_str()) - 1;
                }
           }
        }
        config.close();
    }

    void save_level()
    {
        std::ofstream config;
        config.open("config.txt");
        config << false << std::endl;           //autoConfig disabled
        config << playfieldSize << std::endl;   //Amount of rooms
        for(unsigned int i = 0; i < playfieldSize; i++)  //Saves each room on a new line
        {
            config << abs(roomLookupTable[i] - '0') - 28 << std::endl;
        }
        config << numberOfBats << std::endl;    //Number of bats
        for(unsigned int i = 0; i < numberOfBats; i++)   //Saves each bat on a new line
        {
            config << batLocations[i] << std::endl;
        }
        config << numberOfPits << std::endl;    //Number of pits
        for(unsigned int i = 0; i < numberOfPits; i++)   //Saves each pit on a new line
        {
            config << holeLocations[i] << std::endl;
        }
        config << wumpusRoom;               //Room location of the wumpus
        config.close();
    }

    void write_stats(std::string playername)
    {
        int position = -1;
        for(unsigned int i = 0; i < (statContents.size()); i++) //checks if player is already registered
        {
            if(playername == statContents[i])
            {
                position = i;
            } 
            else
            {
                continue;
            }
        }

        if(position == -1)      //Adds the new statistics to a new player
        {
            statContents.push_back(playername);
            statContents.push_back(std::to_string(amountOfMoves));
            statContents.push_back(std::to_string(amountOfMoves));
        }
        else                    //Adds the new statistics to an existing player
        {
            statContents[position] = playername;
            if(amountOfMoves < std::atoi(statContents[position + 1].c_str()))
            {
                statContents[position + 1] = std::to_string(amountOfMoves);
            }
            statContents[position + 2] = std::to_string((amountOfMoves + std::atoi(statContents[position + 2].c_str())) / 2);
        }
    
        std::ofstream stats;
        stats.open("stats.txt", std::fstream::trunc);   //discards all the data in the file
        for(unsigned int i = 0; i < (statContents.size()); i++)
        {
            stats << statContents[i] << std::endl;
        }
        stats.close();
    }

    std::vector<std::string> send_stats()
    {
        return statContents;
    }
    
    void load_stats()
    {
        std::string line;
        std::ifstream stats;
        stats.open("stats.txt");
        while(std::getline(stats, line))
        {
            statContents.push_back(line);
        }
        stats.close(); 
    }

    unsigned int get_current_room(void)
    {
        return roomLookupTable[currentRoom];
    }


    Possibilities get_possibilities(void)
    {
        return possibleMoves;
    }


    int move(unsigned int room)
    {
        /*if( !valid_direction(room) )
            return PLAYFIELD_ACTION_NOT_POSSIBLE;
        */
        amountOfMoves++; 
        // Calculate index of the room indicated by user
        int index = room_to_index(room);
        if(index < 0)
            return PLAYFIELD_FIELD_DOES_NOT_EXIST;
        
        currentRoom = index;
        calculate_possibilities(possibleMoves, currentRoom); // Recalculate possible directions to move in

        while(playfield_reaction() != PLAYFIELD_OK)
        {
            if(playfield_reaction() != PLAYER_DIED)
                return PLAYER_TELEPORTED;
            return playfield_reaction();
        }

        return PLAYFIELD_OK;
    }


    char smell(void)
    {
        char result = 0x0;

        // Reach 0-2 first ring 3-11 second ring.
        unsigned int reach[12];
        get_reachable_two_moves(reach);

        for(unsigned int i = 0; i < 3; i++)
        {
            if(reach[i] == wumpusRoom)
                result |= SMELL_WUMPUS;
            if(item_in_array(reach[i], bats, numberOfBats))
                result |= SMELL_BATS;
        }

        for (unsigned int i = 3; i < 12; i++)
        {
            if(reach[i] == wumpusRoom)
                result |= SMELL_WUMPUS;
        }
        

        return result;
    }


    int shoot(unsigned int room)
    {
        if( !valid_direction(room) )
            return PLAYFIELD_ACTION_NOT_POSSIBLE;

        if(numberOfArrows == 0)
            return PLAYFIELD_NO_ARROWS;
        
        numberOfArrows--;

        if((int)room == roomLookupTable[wumpusRoom])
            return PLAYFIELD_HIT;
        
        //(Re)spawn wumpus
        spawn_wumpus_at_random();

        //Check whether the wumpus has respawned on player
        if(playfield_reaction() != PLAYFIELD_OK)
            return playfield_reaction();

        return PLAYFIELD_MISS;
    }


    void cleanup(void)
    {
        delete[] roomLookupTable;
        free(bats);
    }
}