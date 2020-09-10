#include <iostream>
#include <vector>
using namespace std;

int compareString(string s1, string s2){
    int length;
    if(s1.length() > s2.length()){
        length = s1.size();
    } else {
        length = s2.size();
    }
    for(int i = 0; i < length; i++){
        if(s1[i] == s2[i]){
            continue;
        } else {
           return i;
        }
    }
    
}

int main(){
    string string1, string2;
    cout << "Geef een zin: " << endl;
    getline(cin, string1);
    cout << "Geef een zin: " << endl;
    getline(cin, string2);
    cout << "Het verschil zit op index: "<< compareString(string1, string2) << endl;
}