cmake_minimum_required(VERSION 3.16)
project(queue_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# --- Флаги MSVC ---
add_compile_options(/W4 /permissive-)

# --- Google Test ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Библиотека с очередью ---
add_library(queue_lib src/queue.cpp
	    include/queue.h
)
target_include_directories(queue_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- Исполняемая программа ---
add_executable(queue_main src/main.cpp)
target_link_libraries(queue_main PRIVATE queue_lib)

# --- Тесты ---
enable_testing()
add_executable(queue_tests tests/test_queue.cpp)
target_link_libraries(queue_tests PRIVATE queue_lib GTest::gtest_main)
target_include_directories(queue_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(queue_tests)