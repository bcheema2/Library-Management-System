cmake_minimum_required(VERSION 3.20)
project(Library_Management_System)

set(CMAKE_CXX_STANDARD 23)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

find_package(fmt REQUIRED)

add_executable(Library_Management_System main.cpp
        src/Catalog.cpp
        src/Student.cpp
        src/Admin.cpp
        include/Transaction.hpp
        src/Transaction.cpp
)

target_include_directories(Library_Management_System PRIVATE
        include
)

target_link_libraries(Library_Management_System PRIVATE fmt::fmt)
