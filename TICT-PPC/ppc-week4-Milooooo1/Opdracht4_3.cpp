#include <iostream>
#include <vector>
using namespace std;

struct furniture {
    int number = 0;
    string name = "";
    float weight = 0.0;
    float length = 0.0;
};

int main(){
    furniture f1 = {};
    cout << "Nummer: ";
    cin >> f1.number;
    cout << "Naam: ";
    cin >> f1.name;
    cout << "Gewicht: ";
    cin >> f1.weight;
    cout << "Lengte: ";
    cin >> f1.length;

    cout << endl;
    cout << f1.name << " heeft nummer " << f1.number << ", weegt " << f1.weight << " en is " << f1.length << " cm." << endl;
}