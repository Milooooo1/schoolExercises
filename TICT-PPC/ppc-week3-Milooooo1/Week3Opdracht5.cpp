#include <iostream>
#include <vector>
using namespace std;

float gemiddelde(vector<int> vect){
    float totaal = 0;
    for(int i = 0; i < vect.size(); i++){
        totaal += vect[i];
    }
    cout << totaal << endl << vect.size() << endl;
    return totaal / vect.size();
}

int main(){
vector<int> vect = {5, 7, 1, 12, 8, 2, 3, 9, 4};
cout << gemiddelde(vect) << endl;

}