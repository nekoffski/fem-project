
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(fem ${SRC_DIR}/main.cpp)
target_link_libraries(fem PUBLIC libfem)
target_include_directories(fem PUBLIC ${FEM_LIB_HEADERS})
