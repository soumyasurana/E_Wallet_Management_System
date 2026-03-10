#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
public:
    std::string name;
    std::string email;
    double balance;

    User() : balance(0.0) {}
    User(const std::string& n, const std::string& e, double b = 0.0)
        : name(n), email(e), balance(b) {}
};

#endif