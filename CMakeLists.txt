# Top level CMakeList
cmake_minimum_required(VERSION 3.10)

project(LevelEditor)

# For now only debug builds. Since also not sure if we have all build/release build of libraries.
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
endif()

set(BINARY_DIR_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(BINARY_DIR_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_DIR_DEBUG}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR_DEBUG})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR_RELEASE})

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        # Not sure if best approach just using CMAKE_RUNTIME_OUTPUT_DIRECTORY as just a variable
        # when a mode is selected as it may still have special meaning/use even if mode is specified.
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
else()
        message("Pick either Debug or Release mode")
endif()

if (WIN32)
        # Winodows precompiled libraries folder
        set(win_lib_folder lib/win)
        set(SDL2_DIR "${win_lib_folder}/SDL2-2.0.12")
        set(SDL2_image_DIR "${win_lib_folder}/SDL2_image-2.0.5")
        set(SDL2_ttf_DIR "${win_lib_folder}/SDL2_ttf-2.0.15")
        set(yaml-cpp_DIR "${win_lib_folder}/yaml-cpp")

        # Link directories where libraries will be searched(when using target_link_libraries).
        # Must be called before add_executable to have effect.
        link_directories("${SDL2_DIR}/lib/x64")
        link_directories("${SDL2_image_DIR}/lib/x64")
        link_directories("${SDL2_ttf_DIR}/lib/x64")
        link_directories("${cpp_DIR}/lib/debug")
endif(WIN32)

# Link againts preinstalled linux libraries
if (UNIX)
        add_compile_options(-g)
        add_link_options(-lSDL2 -lSDL2_image -lSDL2_ttf -lyaml-cpp)
endif(UNIX)

# create core game, level_editor libraries
add_subdirectory(src/core)
add_subdirectory(src/game)
add_subdirectory(src/level_editor)
# create Game, LevelEditor executables
add_subdirectory(src)

enable_testing()
# create GoogleTest test executable
add_subdirectory(src/test)

