//
// Created by Bibenpreet Cheema on 9/30/26.
//

#include "Admin.hpp"


Admin::Admin(const std::string& username, const std::string& name, const std::string& email):
        User{username,
     name,
     email,
      Role::Admin} {}

int Admin::borrowLimit() const {
    return getBorrow();
}
