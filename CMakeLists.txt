cmake_minimum_required(VERSION 3.16)
project(EWalletSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(
    ewallet_core
    src/wallet_service.cpp
    src/storage.cpp
)

target_include_directories(ewallet_core PUBLIC include)

add_executable(
    ewallet
    src/main.cpp
)

target_link_libraries(ewallet PRIVATE ewallet_core)

add_executable(
    ewallet_tests
    tests/wallet_tests.cpp
)

target_link_libraries(ewallet_tests PRIVATE ewallet_core)

add_test(NAME ewallet_tests COMMAND ewallet_tests)
