cmake_minimum_required(VERSION 3.12)
project(Chat)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

file(GLOB_RECURSE SOURCE_FILE "src/*.cpp")

add_executable(Chat ${SOURCE_FILE})
target_include_directories(Chat PRIVATE
    "src/include"
)

target_link_libraries(Chat PRIVATE
    glfw
    glad
)