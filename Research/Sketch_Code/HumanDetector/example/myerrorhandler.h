#ifndef MYERRORHANDLER_H
#define MYERRORHANDLER_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class my_exception : public std::runtime_error {
    std::string msg;
public:
    my_exception(const std::string &arg, const char *file, int line) :
    std::runtime_error(arg) {
        std::ostringstream o;
        o << "\nFile: " << file  << "\nLine: " << line << "\nMessage: " << arg << "\n";
        msg = o.str();
    }
    ~my_exception() throw() {}
    const char *what() const throw() {
        return msg.c_str();
    }
};
#define throw_line(arg) throw my_exception(arg, __FILE__, __LINE__);
#endif // MYERRORHANDLER_H
