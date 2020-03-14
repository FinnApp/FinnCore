project(FinnCore VERSION 0.1 LANGUAGES CXX)

set(SHARED_LIB ${PROJECT_NAME}Shared)
set(STATIC_LIB ${PROJECT_NAME}Static)
set(CORE_OBJECTS ${PROJECT_NAME})
set(INTERFACE_TARGET ${PROJECT_NAME}Interface)

set(SOURCES
    Account.cpp
    Account.hpp
    Wallet.cpp
    Wallet.hpp
    Category.cpp
    Category.hpp
    UniqueEntity.hpp
    NamedEntity.hpp
    NamedEntity.cpp
    Id.hpp
    Id.cpp
    Transaction.hpp
    Transaction.cpp
    EntityContainer.hpp
)

# build object lib with coverage flags and propagate them further
add_library(${CORE_OBJECTS} OBJECT ${SOURCES})
set_target_properties(${CORE_OBJECTS} PROPERTIES POSITION_INDEPENDENT_CODE 1)

option(CODE_COVERAGE "Enable GCC/Clang coverage reporting" ON)
if(CODE_COVERAGE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    target_compile_options(${CORE_OBJECTS} PUBLIC --coverage)
    target_link_options(${CORE_OBJECTS} PUBLIC --coverage)
endif()

# common interface that should be propagated both to static and shared libs
add_library(${INTERFACE_TARGET} INTERFACE)
target_include_directories(${INTERFACE_TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(${INTERFACE_TARGET} INTERFACE
    "$<$<CONFIG:RELEASE>:-O2>"
    "$<$<CONFIG:DEBUG>:-O0>"
)

# link to object library to inherit include dirs and compile options
add_library(${STATIC_LIB} STATIC $<TARGET_OBJECTS:${CORE_OBJECTS}>)
# need to propagate coverage flags only in debug mode otherwise there will be undefined references
target_link_libraries(${STATIC_LIB} PUBLIC ${INTERFACE_TARGET} PUBLIC ${CORE_OBJECTS})

add_library(${SHARED_LIB} SHARED $<TARGET_OBJECTS:${CORE_OBJECTS}>)
# propogate coverage flags to executables
target_link_libraries(${SHARED_LIB} PUBLIC ${INTERFACE_TARGET} PUBLIC ${CORE_OBJECTS})

# set versioning for shared library
set_target_properties(${SHARED_LIB} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${SHARED_LIB} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

install(
    TARGETS
        ${SHARED_LIB} ${STATIC_LIB}
    RUNTIME
        DESTINATION bin # on DLL platforms shared lib goes here
    LIBRARY
        DESTINATION lib # on non-DLL platforms shared lib goes here
    PUBLIC_HEADER
        DESTINATION inlcude
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/
    FILES_MATCHING
        PATTERN "*.hpp"
)
