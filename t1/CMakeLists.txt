cmake_minimum_required(VERSION 3.16)
project(MatrixVariant LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MATRIX_SOURCES
    src/Generator.cpp
    src/ConstantGenerator.cpp
    src/ZeroGenerator.cpp
    src/RandomGenerator.cpp
    src/IStreamGenerator.cpp
    src/Matrix.cpp
    src/Exercise.cpp
    src/Task1.cpp
    src/Task2.cpp
)
add_library(matrix_library STATIC ${MATRIX_SOURCES})
target_include_directories(matrix_library PUBLIC include)

add_executable(matrix_app src/main.cpp)
target_link_libraries(matrix_app PRIVATE matrix_library)

enable_testing()
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()
add_executable(matrix_tests tests/tests.cpp)
target_link_libraries(matrix_tests PRIVATE matrix_library GTest::gtest_main)
add_test(NAME matrix_tests COMMAND matrix_tests)

if(MSVC)
    target_compile_options(matrix_library PRIVATE /W4 /WX)
    target_compile_options(matrix_app PRIVATE /W4 /WX)
    target_compile_options(matrix_tests PRIVATE /W4 /WX)
else()
    target_compile_options(matrix_library PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(matrix_app PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(matrix_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
