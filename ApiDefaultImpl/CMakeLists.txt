cmake_minimum_required(VERSION 3.14)
project(ApiDefaultImpl)

# Add library
add_library(ApiDefaultImpl STATIC
    ApiDefaultImpl.cpp
)

# Include directories
target_include_directories(ApiDefaultImpl PRIVATE
    ${CMAKE_SOURCE_DIR}/Api
    ${CMAKE_SOURCE_DIR}/Core
)

# Link with Api
target_link_libraries(ApiDefaultImpl PRIVATE Api)

set_property(TARGET ApiDefaultImpl PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

add_compile_definitions(
    $<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=2>
    $<$<NOT:$<CONFIG:Debug>>:_ITERATOR_DEBUG_LEVEL=0>
)
