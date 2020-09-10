#include "opdracht1_4_meubels.hpp"

int main(){
    Stool stoel1(4, 1);
    Stool stoel2(4, 1);
    Stool stoel3(4, 1);
    Stool stoel4(4, 1);
    Table table1(4, 120, 60);
    Furniture furniture(stoel1, stoel2, stoel3, stoel4, table1);

    furniture.makeMoreHipster();
    furniture.print();
    return 1;
}