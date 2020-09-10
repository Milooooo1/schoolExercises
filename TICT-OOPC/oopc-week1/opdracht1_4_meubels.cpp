#include "opdracht1_4_meubels.hpp"
#include <iostream>

void Furniture::makeMoreHipster(){
    stoel1.n_legs--;
    stoel2.n_legs--;
    stoel3.n_legs--;
    stoel4.n_legs--;
    table1.n_legs+=4;
};

void Stool::print(){
    std::cout << n_legs << std::endl;
}

void Table::print(){
    std::cout << n_legs << std::endl;
}

void Furniture::print(){
    stoel1.print();
    stoel2.print();
    stoel3.print();
    stoel4.print();
    table1.print();
}