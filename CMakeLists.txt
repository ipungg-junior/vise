cmake_minimum_required(VERSION 3.10)
project(vise)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(core ${SOURCES})
find_package(nlohmann_json 3.0 REQUIRED)
target_link_libraries(core nlohmann_json::nlohmann_json)
