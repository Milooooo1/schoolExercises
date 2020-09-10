#include <iostream>
#include <vector>
using namespace std;

float diff(vector<float> vect){
    float diff;
    for(int i =0; i < vect.size(); i++){
        if((vect[i] - vect[i+1]) > diff){
            diff = vect[i] - vect[i+1];
        } 
    }
    return diff;
}

int main (){
    vector<float> vect = {2.8, 9.6, 9.3, 14.3, 2.8, 18.7, 1.9};
    cout << diff(vect) << endl;
}