file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


add_executable(fem_tests ${TEST_SRC})
target_link_libraries(fem_tests PUBLIC libfem gtest gmock gtest_main gmock_main)
target_include_directories(fem_tests PUBLIC ${FEM_LIB_HEADERS})
