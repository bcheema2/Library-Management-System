//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include "User.hpp"

class Student : public User {
    std::string studentID;
    public:
    Student() = default;
    Student(std::string username, std::string name, std::string email, Role r, std::string ID);

    int borrowLimit() const override;
};
