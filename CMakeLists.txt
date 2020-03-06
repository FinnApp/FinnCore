cmake_minimum_required(VERSION 3.10)

project(FinnCore VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/Account.cpp
    src/Account.hpp
    src/Wallet.cpp
    src/Wallet.hpp
    src/Category.cpp
    src/Category.hpp
    src/Settings.cpp
    src/Settings.hpp
)
add_library(${PROJECT_NAME} OBJECT ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_compile_options(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:RELEASE>:-O2>"
    "$<$<CONFIG:DEBUG>:-O0>"
)

option(CODE_COVERAGE "Enable GCC/Clang coverage reporting" ON)
if(CODE_COVERAGE)
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

option (BUILD_JNI "Build JNI wrapper" ON)
if(BUILD_JNI)
    add_subdirectory(jni)
endif(BUILD_JNI)

add_library(${PROJECT_NAME}Shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)
add_library(${PROJECT_NAME}Static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)

set_property(TARGET ${PROJECT_NAME}Shared PROPERTY POSITION_INDEPENDENT_CODE 1)
set_target_properties(${PROJECT_NAME}Shared PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME}Shared PROPERTIES SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

set_target_properties(${PROJECT_NAME}Shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}Static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}Shared ${PROJECT_NAME}Static
    RUNTIME
        DESTINATION bin # on DLL platforms shared lib goes here
    LIBRARY
        DESTINATION lib # on non-DLL platforms shared lib goes here
    PUBLIC_HEADER
        DESTINATION inlcude
)

install(DIRECTORY src/
    DESTINATION include/
    FILES_MATCHING
        PATTERN "*.hpp"
)
