#ifndef WALLET_SERVICE_HPP
#define WALLET_SERVICE_HPP

#include <unordered_map>
#include <vector>
#include "user.hpp"
#include "transaction.hpp"

class WalletService {
private:
    std::unordered_map<std::string, User> users;
    std::vector<Transaction> transactions;

public:
    WalletService();

    bool registerUser(const std::string& name, const std::string& email);
    bool addFunds(const std::string& email, double amount);
    bool transferFunds(const std::string& from, const std::string& to, double amount);

    double getBalance(const std::string& email);
    void printUsers();

    void save();
};

#endif