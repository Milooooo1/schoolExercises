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

int min(vector<int> vect){
    int min = vect[0];
        for(int i = 1; i < vect.size(); i++){
            if(vect[i] < min){
                min = vect[i];
            }
        }
    return min;
}

float gemVect(vector<int> vect1){
    int sum1 = 0;
    for(int i = 0; i < vect1.size(); i++){
        sum1+=vect1[i];
    }
    return sum1 / (vect1.size());
}

int vectorInput(){
    int input = 0;
    vector<int> vect= {};
    while(input >= 0){
        cout << "Geef een getal: ";
        cin >> input;
        if (input >= 0){
        vect.push_back(input);
        }
    }
    if(controleVector(vect) == 0){
        cout << "De lijst is niet gesorteerd." << endl;
    } else {
        cout << "De lijst is gesorteerd." << endl;
    }
    cout << "Het gemiddelde is: " << gemVect(vect) << endl;
    cout << "De minimum waarde is: " << min(vect) << endl;
    cout << "De reeks bevat " << vect.size() << " getallen." << endl;
}

int main(){
    vectorInput();
}