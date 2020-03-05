cmake_minimum_required(VERSION 3.10)

project(FinnCore VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME} SHARED
    src/Account.cpp
    include/Account.hpp
    src/Wallet.cpp
    include/Wallet.hpp
    src/Category.cpp
    include/Category.hpp
    src/Settings.cpp
    include/Settings.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:RELEASE>:-O2>"
    "$<$<CONFIG:DEBUG>:-O0>"
)

option(CODE_COVERAGE "Enable GCC/Clang coverage reporting" ON)
if(CODE_COVERAGE)
  target_compile_options(${PROJECT_NAME} PRIVATE
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(${PROJECT_NAME} PRIVATE --coverage)
  else()
    target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
  endif()
endif(CODE_COVERAGE)

option (BUILD_TESTING "Build the testing tree" ON)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  enable_testing()
  add_subdirectory(tests)
endif()
