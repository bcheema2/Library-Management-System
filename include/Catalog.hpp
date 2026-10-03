//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "User.hpp"
#include "Book.hpp"

class Catalog {

    std::unordered_map<std::string,std::shared_ptr<Book>> shelf;
    std::unordered_map<std::string,std::vector<std::string>> categories;

    public:
    Catalog() = default;

    void addUser(User& user, std::string& username,std::string& name, std::string& email, User::Role role);
    void findBook(Book& book,const std::string& name) const;
};