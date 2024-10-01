cmake_minimum_required(VERSION 3.10)
project(core)

set(CMAKE_PREFIX_PATH "/usr/include")

set(CMAKE_CXX_STANDARD 11)

# Include direktori header
include_directories(include)

set(nlohmann_json_DIR "/usr/lib/cmake/nlohmann_jsonConfig.cmake")


# Temukan semua file sumber
file(GLOB SOURCES "src/*.cpp")

# Buat executable
add_executable(core ${SOURCES})

# Tautkan library nlohmann_json
target_link_libraries(core nlohmann_json::nlohmann_json)
