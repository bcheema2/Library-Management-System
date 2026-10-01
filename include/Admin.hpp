//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include "User.hpp"
#include "Book.hpp"

class Admin : public User {
    public:
    Admin() {
        setBorrow(30);
    }
    Admin(const std::string& username, const std::string& name, const std::string& email);

    [[nodiscard]] int borrowLimit() const override;
};

