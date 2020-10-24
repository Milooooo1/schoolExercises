#include "note_player_print.hpp"
#include <iostream>

void note_player_print::play( const note & n ){
    std::cout << "Frequency = " << n.frequency << std::endl;  
    std::cout << "Duration = " << n.duration << std::endl;
};

