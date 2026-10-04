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
#include "Transaction.hpp"

class Catalog {
    //for O(1) search of books
    std::unordered_map<std::string, std::unique_ptr<Book>> bookByISBN;

    std::unordered_map<std::string, std::unique_ptr<User>> userByUsername;

    std::unordered_map< std::string, std::vector<std::string>> authorIndex;

    std::vector<Transaction> transactions;

    public:
    Catalog() = default;
    ~Catalog() = default;
    void addBook(std::unique_ptr<Book> books);
    void removeBook(const std::string& isbn);
    std::vector<Book> searchByTitle(const std::string& Title);
    std::vector<Book> searchByAuthor(const std::string& Author);
};
