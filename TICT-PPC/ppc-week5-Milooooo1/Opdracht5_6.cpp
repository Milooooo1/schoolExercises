#include <iostream>
#include <vector>
using namespace std;


float average(vector<float> & vect, unsigned int i){
    if(i == 0){
        return vect[i];
    }

    if(i == vect.size()){
        return average(vect, i-1) / vect.size();
    }
    return vect[i] + average(vect, i-1);
}

int main(){
    vector<float> vect = {3.0,6.0,3.0,1.0};
    cout << average(vect, vect.size()) << endl;
}