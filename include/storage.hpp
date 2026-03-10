#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <filesystem>
#include <unordered_map>
#include <vector>
#include "transaction.hpp"
#include "user.hpp"

class Storage {
public:
    explicit Storage(const std::filesystem::path& dataDirectory);

    void saveUsers(const std::unordered_map<std::string, User>& users) const;
    std::unordered_map<std::string, User> loadUsers() const;

    void saveTransactions(const std::vector<Transaction>& transactions) const;
    std::vector<Transaction> loadTransactions() const;

private:
    std::filesystem::path dataDirectory;
    std::filesystem::path usersFile;
    std::filesystem::path transactionsFile;
};

#endif
