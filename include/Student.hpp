//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include "User.hpp"

class Student : public User {
    public:
    Student() = default;

    void searchCatalog();
    void checkoutBooks();
    void returnBooks();
    void renewItems();
    void fineStatus();

};
