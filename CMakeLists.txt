cmake_minimum_required(VERSION 3.14)
project(AIPlayground)

# Global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
add_definitions(-DUNICODE -D_UNICODE -D_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH -DNOMINMAX)

# Include subprojects
add_subdirectory(AI)
add_subdirectory(Game)
add_subdirectory(App)
add_subdirectory(Api)
add_subdirectory(ApiDefaultImpl)
add_subdirectory(Core)

# Set the startup project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "App")
