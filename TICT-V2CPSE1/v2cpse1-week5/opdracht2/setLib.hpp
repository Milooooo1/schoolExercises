#ifndef _SETLIB_HPP
#define _SETLIB_HPP

#include <array>
#include <iostream>

template < typename T, int N >
class setLib{
private:
    std::array<T, N> intSet;
    int ctr = 0; 

public:
    setLib(){
        for(int i = 0; i <= N; i++){
            intSet[i] = 0;
        }
    }
    void add(T x) {
        if((!contains(x) && ctr < 10) || x == 0){
            intSet[ctr] = x;
            ctr++;
        }
    }

    void remove(T x){
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

    bool contains(T x){
        for(int i = 0; i < N; i++){
            if(intSet[i] == x){
                return true;
            } 
        }
        return false;
    }

    friend std::ostream & operator<<( std::ostream & lhs, const setLib & rhs ){
        for(int i = 0; i < N; i++){
            lhs << rhs.intSet[i] <<", ";
        }
        return lhs;
    }
};

#endif