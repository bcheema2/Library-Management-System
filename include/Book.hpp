//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include <string>

class Book {
    std::string bookName;
    std::string ISBN;
    std::string author;
    std::string category;
    bool isAvailable = false;

    public:
    Book() = default;
    Book(std::string bookName, std::string ISBN, std::string author, std::string category) :
            bookName{std::move(bookName)},
            ISBN{std::move(ISBN)},
            author{std::move(author)},
            category{std::move(category)}
    {}
    [[nodiscard]] std::string getBookName() const noexcept {return bookName;};
    [[nodiscard]] std::string getISBN() const noexcept {return ISBN;};
    [[nodiscard]] std::string getAuthor() const noexcept {return author;};
    [[nodiscard]] std::string getCategory() const noexcept {return category;};
    bool available() const noexcept {return isAvailable;};

    //Setter
    void setAvailable(bool status) {
        isAvailable = status;
    }

    void markBorrowed();
    void markReturned();
    void displayInfo() const;
};

