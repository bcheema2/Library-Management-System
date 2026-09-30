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

    Book& books;
    User& user;
    std::unordered_map<std::string,std::unique_ptr<Book>> shelf;
    std::unordered_map<std::string,std::vector<std::string>> categories;

    public:
    Catalog(Book& books, User& user) : books{books}, user{user} {}

    void addUser(User& user, std::string& username,std::string& name, std::string& email, Role role);
    void findBook(Book& book,std::string& name) const;
};