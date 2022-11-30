file(GLOB_RECURSE tiny_store_source
        ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(
        ${PROJECT_SOURCE_DIR}/src)

add_executable(main ${tiny_store_source})