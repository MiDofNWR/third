cmake_minimum_required(VERSION 3.14)
project(Task3_OOP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(matrix_lib STATIC
    src/RandomGenerator.cpp
    src/IStreamGenerator.cpp
    src/ConstantGenerator.cpp
    src/ZeroGenerator.cpp
    src/Matrix.cpp
    src/Exercise.cpp
    src/Task1.cpp
    src/Task2.cpp
)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app PRIVATE matrix_lib)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(unit_tests tests/test.cpp)
target_link_libraries(unit_tests PRIVATE matrix_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
