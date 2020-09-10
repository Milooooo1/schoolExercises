#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void write_config_file(bool automaticConfig, int fieldSize, std::vector<int> map, int amountOfBats, std::vector<int> bats, int wumpus, int amountOfHoles, std::vector<int> holes)
{
    // Writes all the data to a text file
    std::ofstream config;
    config.open("config.txt");
    config << automaticConfig << std::endl;
    config << fieldSize << std::endl;
    for(int i = 0; i < fieldSize; i++)
    {
        config << map[i] << std::endl;
    }
    config << amountOfBats << std::endl;
    for(int i = 0; i < amountOfBats; i++)
    {
        config << bats[i] << std::endl;
    }
    config << amountOfHoles << std::endl;
    for(int i = 0; i < amountOfHoles; i++)
    {
        config << holes[i] << std::endl;
    }
    config << wumpus;
    config.close();
}

int main()
{
    bool automaticConfig = true;
    int fieldSize = 20;
    int amountOfBats, amountOfHoles = 3;
    int wumpus = 0;
    std::vector<int> map, bats, holes, usedRooms = {};

    std::string input = "";
    std::cout << "Do you want to configure the game manually [y/n] ";
    std::cin >> input;
    if(input == "y" || input == "Y")
    {   // Asks for all the input necessary for the config file.
        int roomInput, batInput, holeInput = 0;
        automaticConfig = false;
        std::cout << "Input field size: ";
        std::cin >> fieldSize;
        std::cout << std::endl;
        std::cout << "Input field layout: " << std::endl;
        for(int i = 0; i < fieldSize; i++)
        {  
            std::cout << "Input: ";
            std::cin >> roomInput;
            map.push_back(roomInput);
        }
        std::cout << "Map input received." << std::endl;
        std::cout << "How many bats would you like in the game?: ";
        std::cin >> amountOfBats;
        for(int i = 0; i < amountOfBats; i++)
        {
            std::cout << "Input: ";
            std::cin >> batInput;
            bats.push_back(batInput);

        }
        std::cout << "Bat's locations received." << std::endl;
        std::cout << "How many bottomless pits would you like in the game?: ";
        std::cin >> amountOfHoles;
        for(int i = 0; i < amountOfHoles; i++)
        {
            std::cout << "Input: ";
            std::cin >> holeInput;
            holes.push_back(holeInput);

        }
        std::cout << "Bottomless pits received." << std::endl;
        std::cout << "In what room would you like the wumpus to be?" << std::endl;
        std::cout << "Wumpus in room: ";
        std::cin >> wumpus;
        std::cout << "Wumpus location received." << std::endl;
    
    }
    else
    {
        std::cout << "Automatic config enabled." << std::endl;
        std::cout << std::endl;
    }

    write_config_file(automaticConfig, fieldSize, map, amountOfBats, bats, wumpus, amountOfHoles, holes);
    
    return 0;
}