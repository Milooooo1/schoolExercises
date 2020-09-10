#include <vector>
#include <iostream>

using namespace std;

struct CountOfDirections {
    int north = 0;
    int east = 0;
    int south = 0;
    int west = 0;
};

int count_num(vector<string>& map, string target, int i){
    if(i == 0){
        return 0;
    } else if (map[i] == target){
        return 1 + count_num(map, target, i - 1);
    } else {
        return count_num(map, target, i - 1);
    }
}

vector<string> reduced_map(CountOfDirections m1){
    vector<string> reducedMap = {};
    if(m1.north > m1.south){
        for(int i = 0; i < (m1.north - m1.south); i++){
            reducedMap.push_back("north");
        }
    } else {
        for(int i = 0; i < (m1.south - m1.north); i++){
            reducedMap.push_back("south");
        }
    }
    if(m1.east > m1.west){
        for(int i = 0; i < (m1.east - m1.west); i++){
            reducedMap.push_back("east");
        }
    } else {
        for(int i = 0; i < (m1.west - m1.east); i++){
            reducedMap.push_back("west");
        }
    }
    return reducedMap; 
}


int main(){
    vector<string> map = {
        "west", "west", "south", "south", "south", "west",
        "west", "west", "north", "north", "north", "north", "north", "west",
        "west", "west", "west", "west", "west", "south", "south", "south",
        "south", "east", "east", "east", "west", "west", "south", "south", 
        "south", "west", "west", "north", "north", "north", "north", "north",
        "north", "west", "west", "west", "west", "west", "west", "south", 
        "south", "south", "south", "east", "east", "east", "north", "north",
        "north", "north", "north", "north", "north", "north", "north", 
        "north", "north", "east", "east", "east", "east", "east", "east", 
        "east", "east", "east", "south", "south", "south", "south", "south",
        "west", "west", "west", "east", "east", "east", "east", "east", 
        "east", "east", "east", "north", "west", "north", "north", "north", 
        "north", "north", "north", "north", "north", "north", "north" 
        };

    CountOfDirections m1 = {
        .north = count_num(map, "north", map.size() - 1 ),
        .east = count_num(map, "east", map.size() - 1 ),
        .south = count_num(map, "south", map.size() - 1 ),
        .west = count_num(map, "west", map.size() - 1 )
    };

    vector<string> reducedMap = reduced_map(m1);
    for(unsigned int i = 0; i < reducedMap.size(); i++){
        std::cout << reducedMap[i] << " ";
    } 
    std::cout << endl;
}