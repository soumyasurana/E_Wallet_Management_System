#ifndef WALLET_SERVICE_HPP
#define WALLET_SERVICE_HPP

#include <filesystem>
#include <unordered_map>
#include <vector>
#include "storage.hpp"
#include "transaction.hpp"
#include "user.hpp"

class WalletService {
private:
    Storage storage;
    std::unordered_map<std::string, User> users;
    std::vector<Transaction> transactions;

public:
    explicit WalletService(const std::filesystem::path& dataDirectory = "data");

    bool registerUser(const std::string& name, const std::string& email);
    bool addFunds(const std::string& email, double amount);
    bool withdrawFunds(const std::string& email, double amount);
    bool transferFunds(const std::string& from, const std::string& to, double amount);

    bool userExists(const std::string& email) const;
    double getBalance(const std::string& email) const;
    std::vector<User> listUsers() const;
    const std::vector<Transaction>& getTransactions() const;
    void printUsers();

    void save();
};

#endif
