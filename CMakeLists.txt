cmake_minimum_required(VERSION 3.20)

project(FinancialEventRouter LANGUAGES CXX)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(router 
    src/main.cpp 
    src/event_parser.cpp
    src/finnhub_client.cpp
)

target_link_libraries(router PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(router PRIVATE CURL::libcurl)