#include <iostream>
#include <vector>
using namespace std;

float gemiddelde(vector<vector<int>> vect){
    float total = 0;
    int totalValues = 0;
    for(int i = 0; i < vect.size(); i++){
        for(int j = 0; j < vect[i].size(); j++){
            total += vect[i][j];
            totalValues++;
        }
    }
    return total / totalValues;
}

int main(){
vector<vector<int>> vect = {
                            {4, 5, 2, 8},
                            {1, 4, 2, 7},
                            {2, 1, 5, 9}, 
                            {3, 1, 6, 1}, 
                            {8, 3, 4, 1},
                           };
cout << gemiddelde(vect) << endl;

}