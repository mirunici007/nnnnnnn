cmake_minimum_required(VERSION 3.30)
project(Manager_Calatorii)

set(CMAKE_CXX_STANDARD 20)

add_executable(Manager_Calatorii
        main.cpp
        password.cpp
        user.cpp
        usersManager.cpp
)
