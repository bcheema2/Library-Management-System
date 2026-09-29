//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include "User.hpp"
#include "Book.hpp"

class Admin : public User , public Book {
    public:
    Admin() = default;

    void addUser(const std::string& name, const std::string& email, const std::string& role);
    void addBooks();
    void deleteBooks();
    void editBooks();
    void generateFine();
    void viewIssueLogs();
};
