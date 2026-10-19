//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include <algorithm>
#include <string>

class Book {
    std::string ISBN;
    std::string author;
    std::string bookName;
    std::string category;
    bool isAvailable = false;
    std::string normalizedTitle;
    std::string normalizedAuthor;

    public:
    Book() = default;
    Book( std::string isbn, std::string auth, std::string bookName, std::string category, bool isAvailable) :
            ISBN{std::move(isbn)},
            author{std::move(auth)},
            bookName{std::move(bookName)},
            category{std::move(category)},
            isAvailable{isAvailable}
            {
                // Converting to lower case for search queries
                normalizedTitle = bookName;
                std::ranges::transform(normalizedTitle, normalizedTitle.begin(),
                [] (const unsigned char c) {return static_cast<char>(std::tolower(c));});

                normalizedAuthor = auth;
                std::ranges::transform(normalizedAuthor, normalizedAuthor.begin(),
                [] (const unsigned char c) {return static_cast<char>(std::tolower(c));});
            }


    [[nodiscard]] const std::string& getBookName() const noexcept {return bookName;}
    [[nodiscard]] const std::string& getISBN() const noexcept {return ISBN;}
    [[nodiscard]] const std::string& getAuthor() const noexcept {return author;}
    [[nodiscard]] const std::string& getCategory() const noexcept {return category;}
    [[nodiscard]] const std::string& getNormalizedTitle() const noexcept {return normalizedTitle;}
    [[nodiscard]] const std::string& getNormalizedAuthor() const noexcept {return normalizedAuthor;}
    [[nodiscard]] bool available() const noexcept {return isAvailable;};

    //Setter
    void setAvailable(const bool status) {
        isAvailable = status;
    }

    void markBorrowed();
    void markReturned();
    void displayInfo() const;
};

