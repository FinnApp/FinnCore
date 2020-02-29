cmake_minimum_required(VERSION 3.5)

project(FinnCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
    Account.cpp
    Account.hpp
    Wallet.cpp
    Wallet.hpp
    Category.cpp
    Category.hpp
    Settings.cpp
    Settings.hpp
)
