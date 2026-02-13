cmake_minimum_required(VERSION 3.10)
project(rof)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(EnTT CONFIG REQUIRED)

add_executable(rof
    main.cpp
    game_map.cpp
    game_map.hpp
    tile.hpp
    point.hpp
)

target_link_libraries(rof PRIVATE EnTT::EnTT)
