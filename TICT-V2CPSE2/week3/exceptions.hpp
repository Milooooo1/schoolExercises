#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP

#include <exception>

namespace error {

class unknown_color : public std::exception {
public:
    unknown_color(const std::string & name ):
        s{ std::string{ "Unknown color ["+name+"]"}}
    {}
    
    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

class end_of_file : public std::exception {
public:
    end_of_file(){
        s = "End of file has been reached.";
    }
    
    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

class invalid_position : public std::exception {
public:
    invalid_position( const char & pos ):
        s{ std::string{ "Invalid postion ["+std::string(1, pos)+"]"} }
    {}
    
    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

class not_a_number : public std::exception {
public:
    not_a_number(const char & pos ):
        s{ std::string{ pos+" is not a number"}}
    {}
    
    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

}
#endif //_EXCEPTIONS_HPP