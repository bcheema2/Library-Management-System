//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include "User.hpp"

class Student : public User {
    std::string studentID;
    double outstandingFines;
    public:
    Student() {
        setBorrow(5);
    }
    Student(std::string username, std::string name, std::string email, Role r, std::string ID, double fines);

    [[nodiscard]] int borrowLimit() const override;
};


