cmake_minimum_required(VERSION 3.20)
project(Library_Management_System)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

# 2. Enable automatic Qt pre-processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

find_package(fmt REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(Library_Management_System main.cpp
        src/Catalog.cpp
        src/Student.cpp
        src/Admin.cpp
        include/Transaction.hpp
        src/Transaction.cpp
        include/StorageManager.hpp
        src/StorageManager.cpp
        include/CLI.hpp
        src/CLI.cpp
)

target_include_directories(Library_Management_System PRIVATE
        include
)

target_link_libraries(Library_Management_System
        PRIVATE fmt::fmt
        PRIVATE Qt6::Widgets
)
