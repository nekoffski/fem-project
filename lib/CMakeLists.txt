set(LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
file(GLOB_RECURSE LIB_SRC ${LIB_SRC_DIR}/*.cpp)

set(CMAKE_CXX_FLAGS "-O3 -mfma")


add_definitions(-DCONFIG_DIR="${MES_CFG_PATH}")

find_package(OpenMP REQUIRED)
add_library(libfem STATIC ${LIB_SRC})
target_link_libraries(libfem PUBLIC jsoncpp_lib OpenMP::OpenMP_CXX)
target_include_directories(libfem PUBLIC ${LIB_SRC_DIR})
