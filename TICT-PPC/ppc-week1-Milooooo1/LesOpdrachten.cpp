#include <iostream>
#include <vector>
using namespace std;

float max(float x, float y) {
    if (x > y){
        return x;
    } else {
        return y;
    }
}

vector<int> doodMuizen(vector<int> gang){
    for(int i = 0; i < gang.size(); i++){
        if(gang[i] == -1){
            gang[i] = 1;
        }
    }
    return gang;
}

int main(){
    cout << max(10.7 , 5.3) << endl;

    vector<int> gang = {1, -1, -1, -1 , 1, -1, 1, -1};
    gang = doodMuizen(gang);
    for(int i = 0; i < gang.size(); i++){
        cout << gang[i] << endl;
    }   


}