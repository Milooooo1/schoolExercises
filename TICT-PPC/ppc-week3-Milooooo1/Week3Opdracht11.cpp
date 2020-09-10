#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> count(vector<vector<int>> vect, int c){
    vector<vector<int>> coordinates;
    for(int i = 0; i < vect.size(); i++){
    int rowCount = 0;
        for(int j = 0; j < vect[i].size(); j++){
            if(vect[i][j] == c){
                rowCount++;
            }
        }
        coordinates.push_back({i, rowCount});
    }
    return coordinates;
}

int main(){
vector<vector<int>> vect{
                            {1, 2, 1},
                            {1, 2, 3},
                            {5, 3, 1}
                        };
vector<vector<int>> vect2 = count(vect, 1);
    for(int i = 0; i < vect2.size(); i++){
        for(int j = 0; j < vect2[i].size(); j++){
            cout << vect2[i][j] ;
        }
        cout << endl;
    }
}