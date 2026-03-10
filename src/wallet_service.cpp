#include "../include/wallet_service.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace {
std::string normalizeEmail(const std::string& value) {
    std::string normalized;
    normalized.reserve(value.size());

    for (unsigned char character : value) {
        if (!std::isspace(character)) {
            normalized.push_back(static_cast<char>(std::tolower(character)));
        }
    }

    return normalized;
}

bool isValidEmail(const std::string& email) {
    const std::size_t atPosition = email.find('@');
    const std::size_t dotPosition = email.rfind('.');

    return atPosition != std::string::npos
        && dotPosition != std::string::npos
        && atPosition > 0
        && dotPosition > atPosition + 1
        && dotPosition + 1 < email.size();
}
}

WalletService::WalletService(const std::filesystem::path& dataDirectory)
    : storage(dataDirectory) {
    users = storage.loadUsers();
    transactions = storage.loadTransactions();
}

bool WalletService::registerUser(const std::string& name, const std::string& email) {
    const std::string normalizedEmail = normalizeEmail(email);

    if (name.empty() || !isValidEmail(normalizedEmail) || users.count(normalizedEmail)) {
        return false;
    }

    users[normalizedEmail] = User(name, normalizedEmail);
    return true;
}

bool WalletService::addFunds(const std::string& email, double amount) {
    const std::string normalizedEmail = normalizeEmail(email);

    if (!users.count(normalizedEmail) || amount <= 0) {
        return false;
    }

    users[normalizedEmail].balance += amount;
    transactions.emplace_back("DEPOSIT", "SYSTEM", normalizedEmail, amount);
    return true;
}

bool WalletService::withdrawFunds(const std::string& email, double amount) {
    const std::string normalizedEmail = normalizeEmail(email);

    if (!users.count(normalizedEmail) || amount <= 0) {
        return false;
    }

    if (users[normalizedEmail].balance < amount) {
        return false;
    }

    users[normalizedEmail].balance -= amount;
    transactions.emplace_back("WITHDRAWAL", normalizedEmail, "SYSTEM", amount);
    return true;
}

bool WalletService::transferFunds(const std::string& from, const std::string& to, double amount) {
    const std::string sender = normalizeEmail(from);
    const std::string recipient = normalizeEmail(to);

    if (!users.count(sender) || !users.count(recipient) || sender == recipient || amount <= 0) {
        return false;
    }

    if (users[sender].balance < amount) {
        return false;
    }

    users[sender].balance -= amount;
    users[recipient].balance += amount;
    transactions.emplace_back("TRANSFER", sender, recipient, amount);
    return true;
}

bool WalletService::userExists(const std::string& email) const {
    return users.count(normalizeEmail(email)) > 0;
}

double WalletService::getBalance(const std::string& email) const {
    const std::string normalizedEmail = normalizeEmail(email);

    if (!users.count(normalizedEmail)) {
        return -1;
    }

    return users.at(normalizedEmail).balance;
}

std::vector<User> WalletService::listUsers() const {
    std::vector<User> result;
    result.reserve(users.size());

    for (const auto& entry : users) {
        result.push_back(entry.second);
    }

    std::sort(result.begin(), result.end(), [](const User& left, const User& right) {
        return left.email < right.email;
    });

    return result;
}

const std::vector<Transaction>& WalletService::getTransactions() const {
    return transactions;
}

void WalletService::printUsers() {
    for (const User& user : listUsers()) {
        std::cout << user.email << " : $" << user.balance << std::endl;
    }
}

void WalletService::save() {
    storage.saveUsers(users);
    storage.saveTransactions(transactions);
}
