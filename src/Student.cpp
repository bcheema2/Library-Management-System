//
// Created by Bibenpreet Cheema on 9/30/26.
//

#include "Student.hpp"

Student::Student( std::string username, std::string name, std::string email, Role r, std::string ID, double fines):
            User(std::move(username),
            std::move(name),
            std::move(email),
            Role::Student),
            studentID{std::move(ID)},
            outstandingFines(fines)
            {};


int Student::borrowLimit() const  {
    return getBorrow();
}
