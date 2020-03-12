project(FinnCoreTests LANGUAGES CXX)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    AccountTests.cpp
    UniqueEntityTests.cpp
    Utils.hpp
    IdTests.cpp
)

target_link_libraries(${PROJECT_NAME}
    FinnCoreShared
    GTest::GTest
    GTest::Main
)

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
