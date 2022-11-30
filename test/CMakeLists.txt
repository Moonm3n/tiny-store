file(GLOB_RECURSE common_test_source
        ${PROJECT_SOURCE_DIR}/src/b_plus_tree.cpp
        ${PROJECT_SOURCE_DIR}/src/file_handler.cpp
        test.cpp)
file(GLOB_RECURSE multi_thread_test_source
        ${PROJECT_SOURCE_DIR}/src/b_plus_tree.cpp
        ${PROJECT_SOURCE_DIR}/src/file_handler.cpp
        multi_thread_test.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(common_test ${common_test_source})
add_executable(multi_thread_test ${multi_thread_test_source})