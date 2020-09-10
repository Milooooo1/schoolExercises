#include <iostream>
#include <vector>
using namespace std;

bool vectControle(vector<int> vect){
    int oneCount = 0;
    int zeroCount = 0;
    for(int i = 0; i < vect.size(); i++){
        if (vect[i] == 1){
            oneCount++;
        } else {
            zeroCount++;
        }
    }
    if(oneCount < zeroCount){
        return false;
    } else if (zeroCount > 12){
        return false;
    } else {
        return true;
    }
}

int main(){
    vector<int> vect = {1,0,0,0,1,1,1,0,0,1,1,0,1};
    cout << vectControle(vect) << endl;
}