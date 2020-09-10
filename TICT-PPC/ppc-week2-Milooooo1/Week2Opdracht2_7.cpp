#include <iostream>
#include <vector>
using namespace std;

int min(vector<int> vect){
    int min = vect[0];
        for(int i = 1; i < vect.size(); i++){
            if(vect[i] < min){
                min = vect[i];
            }
        }
    return min;
}

int max(vector<int> vect){
    int max = vect[0];
        for(int i = 1; i < vect.size(); i++){
            if(vect[i] > max){
                max = vect[i];
            }
        }
    return max;
}

int verschil(vector<int> vect){
    vector<int> vectMax = vect;
    vector<int> vectMin = vect;
    return (max(vectMax) - min(vectMin));
}
int main(){
    vector<int> vect = {4, 8, 1, 2, 4, 12, 3};
    cout << verschil(vect) << endl;
}