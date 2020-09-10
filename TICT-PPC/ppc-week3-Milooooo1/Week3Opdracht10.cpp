#include <iostream>
#include <vector>
using namespace std;

vector<vector<float>>  som(vector<vector<int>> vect){
    float som = 0;
    vector<vector<float>> somVanRij = {{}};
    for(int i = 0; i < vect.size(); i++){
        for(int j = 0; j < vect[i].size(); j++){
            som += vect[i][j];
        }
        somVanRij.push_back({som});
    }
    return somVanRij;
}

int main(){
vector<vector<int>> vect = {
                            {5, 7, 1, 6},
                            {2, 4, 1, 4},
                            {1, 3, 9, 1},
                            {2, 8, 1, 3}
                           };
vector<vector<float>> vect2 = som(vect);
for(int i = 0; i < vect2.size(); i++){
        for(int j = 0; j < vect2[i].size(); j++){
            cout << vect2[i][j] << endl;
        }   
    }
}