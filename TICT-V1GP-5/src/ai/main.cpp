#include "ai.hpp"

#include <iostream>

int main(int argc, const char *argv[])
{
    if(argc != 3)
    {    
        std::cout << "expected 2 argument got:  " << (argc-1) << std::endl;
        std::cout << "Usage: ai EXECUTABLE MAX_NUMBER_OF_PASSES" << std::endl;
        return 1;
    }

    AI::init(argv);
    AI::start();
    AI::cleanup();

    return 0;
}