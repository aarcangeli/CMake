project(CmakeDap)

# cppdap
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third_party/cppdap")

file(GLOB_RECURSE SOURCES "source/*.cpp")
add_library(CMakeDap ${SOURCES})

target_include_directories(CMakeDap PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(CMakeDap PUBLIC HAVE_DAP=1)

target_link_libraries(CMakeDap cppdap)
