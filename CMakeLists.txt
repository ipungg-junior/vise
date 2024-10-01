cmake_minimum_required(VERSION 3.10)
project(core)

set(CMAKE_CXX_STANDARD 11)

# Include direktori header
include_directories(include)

# Temukan nlohmann_json
find_package(nlohmann_json 3.0 REQUIRED)

# Temukan semua file sumber
file(GLOB SOURCES "src/*.cpp")

# Buat executable
add_executable(core ${SOURCES})

# Tautkan library nlohmann_json
target_link_libraries(core nlohmann_json::nlohmann_json)
