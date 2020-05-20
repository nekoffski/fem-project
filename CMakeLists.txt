cmake_minimum_required(VERSION 3.10)
project(fem)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(FEM_LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(MES_CFG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/res/")

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/eigen)

add_subdirectory(3rdparty)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
