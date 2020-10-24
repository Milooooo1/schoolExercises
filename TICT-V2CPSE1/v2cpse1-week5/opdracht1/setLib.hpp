#ifndef _SETLIB_HPP
#define _SETLIB_HPP

#include <array>
#include <iostream>

class setLib{
private:
    std::array<int, 10> intSet = {0,0,0,0,0,0,0,0,0,0};
    int ctr = 0; 

public:
    void add(int x);
    void remove(int x);
    bool contains(int x);
    friend std::ostream & operator<<( std::ostream & lhs, const setLib & rhs );
};

#endif