#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <bitset>
using namespace std;

void improveLoveMessage(uint8_t & message){
    srand(time(0));
    for(int i = 0; i < 4; i++){
        unsigned int randomInt = rand() % 8;
        cout << randomInt << endl;
        cout << bitset<8>(message) << endl;
        message &= ~(0x01 << randomInt);
        cout << bitset<8>(message) << endl;
        message |= (0x01 << randomInt);
        cout << bitset<8>(message) << endl;
    }
    cout << (int)message << endl;
}

int main(){
    uint8_t x = 0x07;
    improveLoveMessage(x);
    return 0;
}