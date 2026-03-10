#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <ctime>

struct Transaction {
    std::string from;
    std::string to;
    double amount;
    std::time_t timestamp;

    Transaction(const std::string& f, const std::string& t, double a)
        : from(f), to(t), amount(a), timestamp(std::time(nullptr)) {}
};

#endif