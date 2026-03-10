#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <unordered_map>
#include "user.hpp"

class Storage {
public:
    static void saveUsers(const std::unordered_map<std::string, User>& users);
    static std::unordered_map<std::string, User> loadUsers();
};

#endif