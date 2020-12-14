#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP

#include <exception>

namespace error {

class syntax_error : public std::exception{
};

class unknown_color : public syntax_error {
public:
    unknown_color(const std::string & name ):
        s{ std::string{ "ERROR: Unknown color ["+name+"]\n"}}
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
        s = "ERROR: End of file has been reached.\n";
    }

    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

class invalid_position : public syntax_error{
public:
    invalid_position( const char & pos ):
        s{ std::string{ "ERROR: Invalid postion ["+std::string(1, pos)+"]\n"} }
    {}

    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

class not_a_number : public syntax_error {
public:
    not_a_number(const char & pos ):
        s{ std::string{pos+" is not a number\n"}}
    {}

    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

class invalid_type : public syntax_error {
public:
    invalid_type( std::string & type):
        s{ std::string{ "ERROR: file contains an invalid type: "+ type+ "\n"} }
    {}

    const char * what() const noexcept override{
        return s.c_str();
    }
private:
  std::string s;
};

class invalid_image : public syntax_error {
public:
    invalid_image( std::string & file ):
        s{ std::string{ "ERROR: Couldn't read image file: "+ file+ "\n"} }
    {}

    const char * what() const noexcept override{
        return s.c_str();
    }
private:
    std::string s;
};

}
#endif //_EXCEPTIONS_HPP
