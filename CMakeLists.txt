cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SRasterizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Set SDL2 and SDL2_image directories
set(SDL2_DIR "${PROJECT_SOURCE_DIR}/lib/SDL")
set(SDL2_IMAGE_DIR "${PROJECT_SOURCE_DIR}/lib/SDL_image")

add_subdirectory(${SDL2_DIR} SDL2_build)
add_subdirectory(${SDL2_IMAGE_DIR} SDL2_image_build)

include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${PROJECT_SOURCE_DIR}/include/Commands 
                    ${SDL2_DIR}/include
                    ${SDL2_IMAGE_DIR}/include)

file(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/Commands/*.cpp)

add_executable(SRasterizer
    ${SRCS}
    main.cpp
)

target_link_libraries(SRasterizer SDL2-static SDL2main SDL2_image)