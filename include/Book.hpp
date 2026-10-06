//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include <algorithm>
#include <string>

class Book {
    std::string bookName;
    std::string ISBN;
    std::string author;
    std::string category;
    std::string normalizedTitle;
    std::string normalizedAuthor;
    bool isAvailable = false;

    public:
    Book() = default;
    Book(std::string bookName, std::string ISBN, std::string author, std::string category) :
            bookName{std::move(bookName)},
            ISBN{std::move(ISBN)},
            author{std::move(author)},
            category{std::move(category)}
            {
                // Converting to lower case for search quesries
                normalizedTitle = bookName;
                std::ranges::transform(normalizedTitle, normalizedTitle.begin(),
                [] (const unsigned char c) {return std::tolower(c);});

                normalizedAuthor = author;
                std::ranges::transform(normalizedAuthor, normalizedAuthor.begin(),
                [] (const unsigned char c) {return std::tolower(c);});
            }


    [[nodiscard]] std::string getBookName() const noexcept {return bookName;}
    [[nodiscard]] std::string getISBN() const noexcept {return ISBN;}
    [[nodiscard]] std::string getAuthor() const noexcept {return author;}
    [[nodiscard]] std::string getCategory() const noexcept {return category;}
    [[nodiscard]] std::string getNormalizedTitle() const noexcept {return normalizedTitle;}
    [[nodiscard]] std::string getNormalizedAuthor() const noexcept {return normalizedAuthor;}
    bool available() const noexcept {return isAvailable;};

    //Setter
    void setAvailable(bool status) {
        isAvailable = status;
    }

    void markBorrowed();
    void markReturned();
    void displayInfo() const;
};

