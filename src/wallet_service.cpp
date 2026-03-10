#include "../include/wallet_service.hpp"
#include "../include/storage.hpp"
#include <iostream>

WalletService::WalletService() {
    users = Storage::loadUsers();
}

bool WalletService::registerUser(const std::string& name, const std::string& email) {

    if (users.count(email))
        return false;

    users[email] = User(name, email);
    return true;
}

bool WalletService::addFunds(const std::string& email, double amount) {

    if (!users.count(email) || amount <= 0)
        return false;

    users[email].balance += amount;

    transactions.emplace_back("SYSTEM", email, amount);

    return true;
}

bool WalletService::transferFunds(const std::string& from, const std::string& to, double amount) {

    if (!users.count(from) || !users.count(to))
        return false;

    if (users[from].balance < amount)
        return false;

    users[from].balance -= amount;
    users[to].balance += amount;

    transactions.emplace_back(from, to, amount);

    return true;
}

double WalletService::getBalance(const std::string& email) {

    if (!users.count(email))
        return -1;

    return users[email].balance;
}

void WalletService::printUsers() {

    for (const auto& u : users) {
        std::cout << u.second.email << " : $" << u.second.balance << std::endl;
    }
}

void WalletService::save() {
    Storage::saveUsers(users);
}