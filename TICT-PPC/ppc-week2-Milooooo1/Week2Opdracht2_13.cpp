#include <vector>
#include <iostream>
using namespace std;

bool controleVector(vector<int> vect){
    for(int i = 0; i < (vect.size() - 1); i++){
        //cout << "Positie: " << i << " Index: "<< vect[i] << " en " << vect[i+1]<< endl;
        if(vect[i] > vect[i+1]){
            return false;
        } 
    } return true;

}

int main(){
    vector<int> vect = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << controleVector(vect) << endl;
}