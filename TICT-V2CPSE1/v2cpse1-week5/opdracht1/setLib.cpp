#include "setLib.hpp"

void setLib::add(int x){
    if((!contains(x) && ctr < 10) || x == 0){
        intSet[ctr] = x;
        ctr++;
    }
}

void setLib::remove(int x){
    if(contains(x)){
        for(int i = 0; i < ctr; i++ ){
            if(x == intSet[i]){
                while(i < ctr){
                        intSet[i] = intSet[i+1];
                        i++;
                }
                if(i == ctr){
                    intSet[i-1] = 0;
                }
            }
        }
        ctr--;
    }
}

bool setLib::contains(int x){
    for(int i = 0; i < 10; i++){
        if(intSet[i] == x){
            return true;
        } 
    }
    return false;
}

std::ostream & operator<<(std::ostream & lhs, const setLib & rhs){
    for(int i = 0; i < 10; i++){
        lhs << rhs.intSet[i] <<", ";
    }
    return lhs;
}