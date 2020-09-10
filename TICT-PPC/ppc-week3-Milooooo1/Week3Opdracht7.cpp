#include <iostream>
#include <vector>
using namespace std;

int returnBit(uint8_t b, int n){
    return (b >> n) & 1U;
}

int main(){
    for(int i = 0; i<8; i++){ // for loop is om te kijken of hij klopt bij elke bit
        cout << returnBit(7, i) << endl;
    }
}