#ifndef OPDRACHT1_3_BOOK_HPP
#define OPDRACHT1_3_BOOK_HPP

#include <ostream>
#include <string.h>

class book{
private:
    std::string text;
    std::string author;
    std::string title;

    void print_text();
    void print_author();
    void print_title();

public:
    book(const std::string & text, const std::string & author, const std::string & title):
        text( text ),
        author( author ),
        title( title )
    {}

    void print();
};

#endif // OPDRACHT1_3_BOOK_HPP