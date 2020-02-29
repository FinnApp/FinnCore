cmake_minimum_required(VERSION 3.10)

project(FinnCore VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED
    Account.cpp
    Account.hpp
    Wallet.cpp
    Wallet.hpp
    Category.cpp
    Category.hpp
    Settings.cpp
    Settings.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

enable_testing()
add_subdirectory(tests)
