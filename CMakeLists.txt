cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SRasterizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS})

file(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(SRasterizer
    ${SRCS}
    main.cpp
)

target_link_libraries(SRasterizer ${SDL2_LIBRARIES})