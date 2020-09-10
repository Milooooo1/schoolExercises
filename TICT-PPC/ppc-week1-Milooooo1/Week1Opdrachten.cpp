#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
using namespace std;

void exerciseEenEen(){
	int getalA;
	int getalB;
	cout << "Vul een getal in: ";
	cin >> getalA;
	cout << "Vul nog een ander getal in: ";
	cin >> getalB;
	int modulo = getalA % getalB;
	cout << "Het overgebleven modulo van de twee getallen is: " << modulo << "\n";
}

void exerciseEenTwee() {
/* 
1
	a: 97
	b: 98
	c: 99
	d: 100
	z: 122
2
	A: 65
	B: 66
	C: 67
	H: 72
	Z: 90
3
	Verschil A - a + g = G
4
	8: 56
	0: 48
5
	decimale waarde van '4' - '0' = 4
6
	Het antwoord van vraag 3 is handig om een een hoofdletter van te maken.
	Het antwoord van vraag 5 is handig om een letter te zien als een getal.
*/
}

void exerciseEenDrie(){
	int x = 8.2;
	char c = 'b' + ('Z'- 'z');
	int f = '8' - '0';
	bool u = 8 >= 10;

	string p = "Hoera!";
	p.append(" HIEP!");
	string station = string("Driebergen") + "-Zeist";
	string plaats = station.erase(10, station.size()-10);

	int y = 18 / 5;
	int z = 18 / 5.0;
	float t = 18 / 5;
	float s = 18 / 5.0;
	int e = 10 % 3;
	bool b = true && (false || true);
	cout << "x = 8 \n";
	cout << "c = B \n";
	cout << "f = 8 \n";
	cout << "u = false \n";
	cout << "p = Hoera! HIEP! \n";
	cout << "station = Driebergen-Zeist \n";
	cout << "plaats = Driebergen \n";
	cout << "y = 3 \n";
	cout << "z = 3 \n";
	cout << "t = 3 \n";
	cout << "s = 3.6 \n";
	cout << "e = 1 \n";
	cout << "b = true \n\n";
}

void exerciseEenVier() {
	cout << "De output is 65, 70, 73, 74, 77, 78, 81, 84, 87, 90 \n";
	 /* 
	 * int number = 65;
	number = 70;
	while(number < 90){
		cout << number;
		if(number < 70){
			number++;
		}else if (number < 80){
			number +=3;
		}
	} */
}

void exerciseEenVijf(){
	//Beschrijf de volgende code:
	/*
	char letter ='a';
	for(int i=0; i < 26; i++){
		cout << char(letter + i) << ", ";
	}
	*/
	cout << "De bovenstaande code print het hele alfabet\n\n";
}

void exerciseEenZes(){
	char invoer;
	cout << "Voer een character in: ";
	cin >> invoer;
	cout << "De uitkomst is: " << int(invoer) + 32 << "\n\n";
}

void exerciseEenZeven(){
	string invoer;
	cout << "Voer de zin in die u wilt vertalen: ";
	getline(cin.ignore(), invoer);
	for(int i = 0; i < invoer.length(); i++){
		if(invoer[i] == 'e'){
			invoer[i] = '3';
		} else if( invoer[i] == 'l'){
			invoer[i] = '1';
		} else if( invoer[i] == 't'){
			invoer[i] = '7';
		} else if( invoer[i] == 'o'){
			invoer[i] = '0';
		} else if( invoer[i] == ' '){
		    continue;
		} else {
			char j = invoer[i];
			j = int(j) - 32;
			invoer[i] = j;
			}
		}
	cout << invoer << endl;
}

void exerciseEenAcht(){
	int grootte;
	cout << "Hoe groot? ";
	cin >> grootte;
	
	for(int i =0; i <= grootte; i++){
	    for(int i =0; i <= grootte; i++){
	        cout << "*";
	    }
	    cout << endl;
	}
}
	
void exerciseEenNegen(){
	int grootte;
	cout << "Hoe groot? ";
	cin >> grootte;
	
	for(int i =0; i < grootte; i++){
	    for(int j =0; j <= i; j++){
	        cout << "*";
	    }
	    cout << endl;
	}
}
	
void exerciseEenTien(){
	int grootte;
    cout << "Hoe groot: ";
    cin >> grootte;
    for(int i = grootte; i >= 1; --i)
    {
        for(int j = 1; j <= i; ++j)
        {
            cout << "*";
        }
        cout << endl;
    }
}
	
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
	bool running = true;
	int counter = 0;
	pyramide = "";
	while(running == 1){
		pyramide = pyramide + "*";
		cout << pyramide << endl;
		if(counter < grootte){
			counter++;
		}
	}
}
	
void exerciseEenTwaalf(){
	//Ik denk dat deze een stuk makkelijker kan maar ik kwam er echt niet uit.
	int grootte;
    cout << "Hoe groot: ";
    cin >> grootte;
    int counter = 0;
    int counter2 = grootte - 1;
    for(int i = grootte; i >= 1; i--){
        for(int j = 1; j < i; j++){
            cout << " ";
        }
        for(int x = 0; x <= counter; x++){
            cout<<"*";
        }
    counter++;
	cout << endl;
    }
	for(int i = 0; i < grootte; i++){
	    for(int j = 0; j <= i; j++){
	        cout << " ";
	    }
	    for(int x = counter2; x >= 1; x--){
	        cout << "*";
	    }
	counter2--;
	cout << endl;
	}
}

int main() {
	cout << "Opdracht 1.1 wordt uitgevoerd.\n";
	exerciseEenEen();
	cout << "\nOpdracht 1.2 wordt uitgevoerd.\n";
	exerciseEenTwee();
	cout << "Opdracht 1.3 wordt uitgevoerd.\n";
	exerciseEenDrie();
	cout << "Opdracht 1.4 wordt uitgevoerd.\n";
	exerciseEenVier();
	cout << "\nOpdracht 1.5 wordt uitgevoerd.\n";
	exerciseEenVijf();
	cout << "Opdracht 1.6 wordt uitgevoerd.\n";
	exerciseEenZes();
	cout << "Opdracht 1.7 wordt uitgevoerd.\n";
	exerciseEenZeven();
	cout << "\nOpdracht 1.8 wordt uitgevoerd.\n";
	exerciseEenAcht();
	cout << "\nOpdracht 1.9 wordt uitgevoerd.\n";
	exerciseEenNegen();
	cout << "\nOpdracht 1.10 wordt uitgevoerd.\n";
	exerciseEenTien();
	cout << "\nOpdracht 1.11 wordt uitgevoerd.\n";
	exerciseEenElf();
	cout << "\nOpdracht 1.12 wordt uitgevoerd.\n";
	exerciseEenTwaalf();
	
}
