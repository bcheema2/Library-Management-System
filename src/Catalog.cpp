//
// Created by Bibenpreet Cheema on 9/30/26.
//
#include "Catalog.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

void Catalog:: findBook(Book& book, std::string& name) const {
    if (shelf.contains(name)) {
        book.setAvailable(true);
        std:: cout << "Book is available\n";
    }
    else {
        book.setAvailable(false);
        std:: cout << "Book is unavailable\n";
    }
}
