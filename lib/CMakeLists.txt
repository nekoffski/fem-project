set(LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
file(GLOB_RECURSE LIB_SRC ${LIB_SRC_DIR}/*.cpp)

add_definitions(-DCONFIG_DIR="${MES_CFG_PATH}")
add_library(libfem STATIC ${LIB_SRC})
target_link_libraries(libfem PUBLIC jsoncpp_lib)
target_include_directories(libfem PUBLIC ${LIB_SRC_DIR})
