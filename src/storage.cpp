#include "../include/storage.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace {
std::string readQuotedField(std::istringstream& input) {
    std::string value;
    input >> std::quoted(value);
    return value;
}
}

Storage::Storage(const std::filesystem::path& directory)
    : dataDirectory(directory),
      usersFile(dataDirectory / "users.db"),
      transactionsFile(dataDirectory / "transactions.db") {}

void Storage::saveUsers(const std::unordered_map<std::string, User>& users) const {
    std::filesystem::create_directories(dataDirectory);
    std::ofstream file(usersFile);

    for (const auto& pair : users) {
        file << std::quoted(pair.second.name) << ' '
             << std::quoted(pair.second.email) << ' '
             << std::fixed << std::setprecision(2) << pair.second.balance << "\n";
    }
}

std::unordered_map<std::string, User> Storage::loadUsers() const {
    std::unordered_map<std::string, User> users;
    std::ifstream file(usersFile);
    std::string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream ss(line);
        const std::string name = readQuotedField(ss);
        const std::string email = readQuotedField(ss);
        double balance = 0.0;

        if (!email.empty() && (ss >> balance)) {
            users[email] = User(name, email, balance);
        }
    }

    return users;
}

void Storage::saveTransactions(const std::vector<Transaction>& transactions) const {
    std::filesystem::create_directories(dataDirectory);
    std::ofstream file(transactionsFile);

    for (const Transaction& transaction : transactions) {
        file << std::quoted(transaction.type) << ' '
             << std::quoted(transaction.from) << ' '
             << std::quoted(transaction.to) << ' '
             << std::fixed << std::setprecision(2) << transaction.amount << ' '
             << transaction.timestamp << "\n";
    }
}

std::vector<Transaction> Storage::loadTransactions() const {
    std::vector<Transaction> transactions;
    std::ifstream file(transactionsFile);
    std::string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream ss(line);
        const std::string type = readQuotedField(ss);
        const std::string from = readQuotedField(ss);
        const std::string to = readQuotedField(ss);
        double amount = 0.0;
        std::time_t timestamp = 0;

        if (ss >> amount >> timestamp) {
            transactions.emplace_back(type, from, to, amount, timestamp);
        }
    }

    return transactions;
}
