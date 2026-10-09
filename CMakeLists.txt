cmake_minimum_required(VERSION 3.20)

project(FinancialEventRouter LANGUAGES CXX)

find_package(CURL REQUIRED)

add_executable(router src/main.cpp)

target_link_libraries(router PRIVATE CURL::libcurl)