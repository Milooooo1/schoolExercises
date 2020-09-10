#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<vector<int>> mat = { {-1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                {-1, 0, -1,  0,  0,  0, -1, -1,  0, -1, -1},
                                {-1, 0, -1,  0, -1, -1, -1,  0,  0,  1, -1},
                                {-1, 0,  0,  0,  0,  0,  0,  0, -1, -1, -1},
                                {-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
                              };
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++){
            if(mat[i][j] == -1){
                mat[i][j] = 'x';
                cout << (char)mat[i][j];
            } else {
            cout << mat[i][j];
            }   
        }   cout << endl;
    }
}
