cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SRasterizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${PROJECT_SOURCE_DIR}/include/Commands 
                    ${PROJECT_SOURCE_DIR}/external/SDL2 
                    ${PROJECT_SOURCE_DIR}/external/SDL2_image)

file(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp 
                ${PROJECT_SOURCE_DIR}/src/Commands/*cpp)

add_executable(SRasterizer
    ${SRCS}
    main.cpp
)

target_link_libraries(SRasterizer SDL2 SDL2main SDL2_image)