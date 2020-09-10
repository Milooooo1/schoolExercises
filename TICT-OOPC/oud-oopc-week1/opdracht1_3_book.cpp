#include <iostream>
#include "opdracht1_3_book.hpp"

void book::print(){
    print_title();
    print_author();
    print_text();
}

void book::print_text(){
    std::cout << text << std::endl;
}

void book::print_title(){
    std::cout << title << std::endl;
}

void book::print_author(){
    std::cout << author << std::endl;
}