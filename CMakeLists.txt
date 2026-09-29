cmake_minimum_required(VERSION 4.3)
project(Library_Management_System)

set(CMAKE_CXX_STANDARD 23)

add_executable(Library_Management_System main.cpp
        include/Admin.hpp
        include/User.hpp
        include/Student.hpp
        include/Book.hpp
        include/Catalog.hpp
        include/Catalog.hpp)
