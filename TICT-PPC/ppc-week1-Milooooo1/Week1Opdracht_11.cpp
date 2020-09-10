#include <iostream>
using namespace std;

void exerciseEenElf(){
	cout << "Opdracht 11 met for loop: " << endl;
	int grootte;
    cout << "Hoe groot: ";
    cin >> grootte;
	string pyramide = "";
	for(int i = 0; i < grootte; i++){
	    pyramide = pyramide + "*";
		cout << pyramide << endl;
	} for(int j = grootte; j > 1; j--){
	    pyramide.erase(0,1);
	    cout << pyramide << endl;
	}
	cout << "Opdracht 11 met while loop: " << endl;
	int counter = 0;
	pyramide = "";
	while(counter < grootte){
		pyramide = pyramide + "*";
		cout << pyramide << endl;
        counter++;
	}
    while(counter > 0){
	    pyramide.erase(0,1);
	    cout << pyramide << endl;
        counter--;
    }
}

int main(){
    exerciseEenElf();
}