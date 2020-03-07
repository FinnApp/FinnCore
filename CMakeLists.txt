cmake_minimum_required(VERSION 3.10)

project(FinnCore VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SHARED_LIB ${PROJECT_NAME}Shared)
set(STATIC_LIB ${PROJECT_NAME}Static)

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

# common options both for static and shared libs
add_library(${PROJECT_NAME} OBJECT ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_compile_options(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:RELEASE>:-O2>"
    "$<$<CONFIG:DEBUG>:-O0>"
)

# link to object library to inherit include dirs and compile options
add_library(${STATIC_LIB} STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)
target_link_libraries(${STATIC_LIB} ${PROJECT_NAME})

add_library(${SHARED_LIB} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)
target_link_libraries(${SHARED_LIB} ${PROJECT_NAME})
# set versioning for shared library
set_target_properties(${SHARED_LIB} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${SHARED_LIB} PROPERTIES SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
set_target_properties(${SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

option(CODE_COVERAGE "Enable GCC/Clang coverage reporting" ON)
# enable only for shared library in debug mode
if(CODE_COVERAGE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  target_compile_options(${SHARED_LIB} PRIVATE --coverage)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(${SHARED_LIB} PRIVATE --coverage)
  else()
    target_link_libraries(${SHARED_LIB} PRIVATE --coverage)
  endif()
endif()

install(TARGETS ${SHARED_LIB} ${STATIC_LIB}
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
