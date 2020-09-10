#include <iostream>
#include <vector>
using namespace std;

float maxVect(vector<float> vect, int i){
    if(i == 1){
        return vect[0]; 
    }
    return max(vect[i-1], maxVect(vect, i-1)); 
}

int main(){
    vector<float> my_vect = {13.0f, 0.6f, 7.2f, 2.1f, 9.8f, 12.0f, 3.5f};
    cout << maxVect(my_vect, my_vect.size()) << endl;
}