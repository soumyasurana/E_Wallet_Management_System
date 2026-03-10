#include "../include/storage.hpp"
#include <fstream>
#include <sstream>

void Storage::saveUsers(const std::unordered_map<std::string, User>& users) {
    std::ofstream file("data/users.db");

    for (const auto& pair : users) {
        file << pair.second.name << ","
             << pair.second.email << ","
             << pair.second.balance << "\n";
    }
}

std::unordered_map<std::string, User> Storage::loadUsers() {

    std::unordered_map<std::string, User> users;

    std::ifstream file("data/users.db");
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, email, balanceStr;

        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, balanceStr);

        users[email] = User(name, email, std::stod(balanceStr));
    }

    return users;
}