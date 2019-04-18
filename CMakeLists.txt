cmake_minimum_required(VERSION 3.13)
project(CCP_plazza_2018)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB_RECURSE MY_SRC
        "include/*.hpp"
        "*.cpp"
        )

add_executable(${PROJECT_NAME} ${MY_SRC})