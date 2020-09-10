#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> getIndexes(const vector<vector<char>> & charMatrix, const char & c){
    vector<vector<int>> coordinates;
    for(int i = 0; i < charMatrix.size(); i++){
        for(int j = 0; j < charMatrix[i].size(); j++){
            if(charMatrix[i][j] == c){
                coordinates.push_back({i, j});
            }
        }
    }
    return coordinates;
}

int main(){
    char searchChar = 'u';
    vector<vector<char>> letters = {
                                    {'u', 'b', 'c', 'p'},
                                    {'f', 'b', 'y', 'u'},
                                    {'t', 'u', 'u', 's'},
                                    {'x', 'u', 'w', 'q'}
                                   };
    vector<vector<int>> indexes = getIndexes(letters, searchChar);
    
    cout << "there is a "<< searchChar << " at: ";
    for(unsigned int i = 0; i < indexes.size(); i++){
        cout << "[" << indexes[i][0] << ", " << indexes[i][1] << "],";
    }
    cout << endl;
}