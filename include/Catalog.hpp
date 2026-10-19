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

    std::unordered_map<std::string, std::shared_ptr<User>> userByUsername;

    std::unordered_map< std::string, std::vector<std::string>> authorIndex;

    std::vector<Transaction> activeTransactions;

    // Filenames for load state and save state

    std::string bookFile;
    std::string userFile;

    public:
    Catalog(std::string bFile = "books.txt", std::string uFile = "users.txt");

    ~Catalog();

    void addBook(std::unique_ptr<Book> book);
    void removeBook(const std::string& isbn);
    [[nodiscard]] std::vector<const Book*> searchByTitle(const std::string& title) const;
    [[nodiscard]] std::vector<const Book*> searchByAuthor(const std::string& author) const;

    bool registerUser(std::unique_ptr<User> user);
    [[nodiscard]] std::shared_ptr<User> authenticateUser(const std::string& username) const;

    bool issueBook(const std::string& username, const std::string& isbn);
    bool returnBook(const std::string& username, const std::string& isbn);
};
