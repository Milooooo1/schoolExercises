#ifndef OPDRACHT1_4_MEUBELS_HPP
#define OPDRACHT1_4_MEUBELS_HPP

#include <ostream>

class Stool{
private:

public:
    int n_legs;
    int n_seats;
    Stool(const int & n_legs, const int & n_seats):
        n_legs( n_legs ),
        n_seats( n_seats )
    {}
    void print();
};

class Table{
private:

public:
    int n_legs;
    int length;
    int width;

    Table(const int & n_legs, const int & length, const int & width):
        n_legs( n_legs ),
        length( length ),
        width( width)
    {}
    void print();
};

class Furniture{
private:
    Stool stoel1;
    Stool stoel2;
    Stool stoel3;
    Stool stoel4;
    Table table1;

public:
    Furniture(const Stool & stoel1, const Stool & stoel2, const Stool & stoel3, const Stool & stoel4, const Table & table1):
        stoel1( stoel1 ),
        stoel2( stoel2 ),
        stoel3( stoel3 ),
        stoel4( stoel4 ),
        table1( table1 )  
    {}
    void print();
    void makeMoreHipster();
};

#endif  /* OPDRACHT1_4_BOOK_HPP */