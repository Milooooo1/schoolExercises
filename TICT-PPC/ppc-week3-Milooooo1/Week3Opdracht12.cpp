#include <iostream>
#include <vector>
using namespace std;

void transpose(vector<vector<int>> & team){
    unsigned int tmp = 0;
    vector<vector<int>> tmpVect = {{}};
    for(int i = 0; i < team.size(); i++){
        for(int j = i; j < team[i].size(); j++){
            tmp = team[i][j];
            team[i][j] = team[j][i];
            team[j][i] = tmp;
        }
    }
}

int main(){
vector<vector<int>> team = { {1,2,3},
                             {4,5,6},
                             {7,8,9}
                           };

    transpose(team);

    for(int i = 0; i < team.size(); i++){
        for(int j = 0; j < team[i].size(); j++){
            cout << team[i][j] << ',';
        }
        cout << endl;
    }
}