cmake_minimum_required(VERSION 3.10)
project(EWalletSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    ewallet
    src/main.cpp
    src/wallet_service.cpp
    src/storage.cpp
)