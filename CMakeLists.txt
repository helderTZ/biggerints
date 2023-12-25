project(biggerints)
cmake_minimum_required(VERSION 3.16)

set(CXX_STANDARD 17)

add_library(biggerints INTERFACE)
target_include_directories(biggerints INTERFACE include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_compile_options (-Wall -Wextra -std=c++17)

add_executable(test_biggerints test/test_biggerints.cpp)
target_link_libraries(test_biggerints biggerints gtest_main)
gtest_discover_tests(test_biggerints)