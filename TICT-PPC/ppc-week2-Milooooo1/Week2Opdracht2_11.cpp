#include <iostream>
#include <vector>
using namespace std;

float sumVectors(vector<float> vect1, vector<float> vect2){
    float sum1 = 0;
    float sum2 = 0;
    for(int i = 0; i < vect1.size(); i++){
        sum1+=vect1[i];
    }
    for(int i = 0; i < vect2.size(); i++){
        sum2+=vect2[i];
    }
    return sum1 + sum2;
}
int main(){
    vector<float> vect1 = {2.5, 1.3, 9.7, 4.3};
    vector<float> vect2 = {1.3, 4.8, 1.2, 9,1};
    cout << sumVectors(vect1, vect2) << endl;
}