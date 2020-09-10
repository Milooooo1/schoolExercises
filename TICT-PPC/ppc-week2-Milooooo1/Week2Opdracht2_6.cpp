#include <iostream>
#include <vector>
using namespace std;

float min(vector<float> vect){
    float min = vect[0];
        for(int i = 1; i < vect.size(); i++){
            if(vect[i] < min){
                min = vect[i];
            }
        }
    return min;
}

int main(){
    vector<float> vect = {4.3, 8.9, 1.2, 2, 4, 12, 3};
    cout << min(vect) << endl;
}