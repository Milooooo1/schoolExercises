#include "note_player_print.hpp"
#include <iostream>
#include <fstream>
#include <string>

void note_player_print::play( const note & n ){
    std::cout << "Frequency = " << n.frequency << std::endl;  
    std::cout << "Duration = " << n.duration << std::endl;
    std::cout << "===================" << std::endl;

    std::fstream file;
    file.open("melody.cpp");


    file.seekg(std::ios::beg);                                                          // Skip the first 3 lines
    for(int i = 0; i < 3 + runtime ; i++ ){
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int frequency = n.frequency;
    int duration = n.duration;
    file << "\tp.play( note{ note::"<< frequency << ",\tnote::" << duration << " \t} );\n";
    file << "}\n";


    file.close();  
    runtime++;
};

