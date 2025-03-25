cmake_minimum_required(VERSION 3.28)
project(password_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(password_manager
        src/main.cpp
        src/PasswordManager.cpp
        src/PasswordEntry.cpp
)

target_include_directories(password_manager PRIVATE include)
