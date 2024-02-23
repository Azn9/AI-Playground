cmake_minimum_required(VERSION 3.14)
project(App)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Add library
add_executable(App WIN32
    App.cpp
    ${CMAKE_SOURCE_DIR}/App/App.rc
)

# Include directories
target_include_directories(App PRIVATE
    libs/physx_include
    Core
)

# Include directories
target_include_directories(App PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/physx_include
    ${CMAKE_SOURCE_DIR}/Core
    ${CMAKE_SOURCE_DIR}/Api
)

link_directories(${CMAKE_SOURCE_DIR}/libs)

# Link libraries
target_link_libraries(App PRIVATE
    debug ${CMAKE_SOURCE_DIR}/libs/debug/effects11d.lib optimized ${CMAKE_SOURCE_DIR}/libs/release/effects11.lib
    debug ${CMAKE_SOURCE_DIR}/libs/debug/PhysX_64.lib optimized ${CMAKE_SOURCE_DIR}/libs/release/PhysX_64.lib
    debug ${CMAKE_SOURCE_DIR}/libs/debug/PhysXCommon_64.lib optimized ${CMAKE_SOURCE_DIR}/libs/release/PhysXCommon_64.lib
    debug ${CMAKE_SOURCE_DIR}/libs/debug/PhysXCooking_64.lib optimized ${CMAKE_SOURCE_DIR}/libs/release/PhysXCooking_64.lib
    debug ${CMAKE_SOURCE_DIR}/libs/debug/PhysXExtensions_static_64.lib optimized ${CMAKE_SOURCE_DIR}/libs/release/PhysXExtensions_static_64.lib
    debug ${CMAKE_SOURCE_DIR}/libs/debug/PhysXFoundation_64.lib optimized ${CMAKE_SOURCE_DIR}/libs/release/PhysXFoundation_64.lib
    debug ${CMAKE_SOURCE_DIR}/libs/debug/PhysXPvdSDK_static_64.lib optimized ${CMAKE_SOURCE_DIR}/libs/release/PhysXPvdSDK_static_64.lib
    dinput8.lib
    dxguid.lib
    d3d11.lib
    d3dcompiler.lib
    dxgi.lib
    "${TORCH_LIBRARIES}"
    Game
    AI
    Core
    Api
)

# file(GLOB TORCH_DLLS "${CMAKE_SOURCE_DIR}/libtorch/lib/*.dll")
# add_custom_command(TARGET App POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_if_different "${TORCH_DLLS}" "$<TARGET_FILE_DIR:App>"
# )

# Post-build command to copy DLLs
add_custom_command(TARGET App POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/dlls" "$<TARGET_FILE_DIR:App>"
)

set_target_properties(App PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/data"
)

set_property(TARGET App PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

add_compile_definitions(
    $<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=2>
    $<$<NOT:$<CONFIG:Debug>>:_ITERATOR_DEBUG_LEVEL=0>
)
