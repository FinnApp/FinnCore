cmake_minimum_required(VERSION 3.10)

project(FinnCoreJni VERSION ${PROJECT_VERSION} LANGUAGES CXX)

find_package(JNI REQUIRED)

add_library(${PROJECT_NAME} SHARED
    JniAccount.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${JNI_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${JNI_LIBRARIES}
    FinnCore
)
target_compile_options(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:RELEASE>:-O2>"
    "$<$<CONFIG:DEBUG>:-O0>"
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME
        DESTINATION bin # on DLL platforms shared lib goes here
    LIBRARY
        DESTINATION lib # on non-DLL platforms shared lib goes here
    PUBLIC_HEADER
        DESTINATION inlcude
)
