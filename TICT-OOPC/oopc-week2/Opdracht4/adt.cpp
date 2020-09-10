#include "adt.hpp"

    vector::vector(int x, int y):
        x(x),
        y(y)
    {}

    bool vector::operator==(const vector & rhs) const {
        return( x == rhs.x && y == rhs.y);
    }

    vector vector::operator+(const vector & rhs) const { 
        return vector( x + rhs.x, y + rhs.y);
    }

    vector vector::operator+(const vector & lhs, const vector & rhs){
        return vector( lhs.x + rhs.x, lhs.y + rhs.y);
    }

    vector & vector::operator+=(const vector & rhs){
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vector vector::operator*(const vector & rhs) const {
        //std::cout << x << " " << rhs.x << " " << y << " " << rhs.y;           
        return vector((x * rhs.x),(y * rhs.y));
    }

    vector vector::operator*(const vector & lhs, const int x){
        return vector(lhs.x * x, lhs.y * x);
    } 

    vector vector::operator*(const int x, const vector & rhs){
        return vector(rhs.x * x, rhs.y * x);
    }

    vector & vector::operator*=(const vector & rhs){                 
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    std::ostream & operator<<(std::ostream & lhs, const vector & rhs) {
         return lhs << std::hex <<"0x" std::setfill('0') << std::setw(2) << rhs.x << " , " << "0x" std::setfill('0') << std::setw(2)  << rhs.y;
    }