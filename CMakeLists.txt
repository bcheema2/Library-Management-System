cmake_minimum_required(VERSION 4.3)
project(Library_Management_System)

set(CMAKE_CXX_STANDARD 23)

add_executable(Library_Management_System main.cpp
        src/Catalog.cpp
        src/Student.cpp
        src/Admin.cpp
        include/Transaction.hpp
)

target_include_directories(Library_Management_System PRIVATE include)
