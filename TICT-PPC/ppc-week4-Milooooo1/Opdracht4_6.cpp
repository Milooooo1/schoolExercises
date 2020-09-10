#include <iostream>
#include <bitset>
#define INT_BITS 8
using namespace std;

int cycleBits(int bit, int amount){
    if(amount > 0){
        return (bit << amount)|(bit >> (INT_BITS - amount));
    } else {
        return (bit >> abs(amount))|(bit << (INT_BITS - abs(amount)));
    }
}

int main(){
    cout << cycleBits(8, 2) << endl;
}