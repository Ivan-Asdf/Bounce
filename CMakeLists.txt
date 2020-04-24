cmake_minimum_required(VERSION 3.10)

project(LevelEditor)

# For now only debug builds. Since also not sure if we have all build/release build of libraries.
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
endif()

set(BINARY_DIR_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(BINARY_DIR_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
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
        set(SDL2_DIR "dep_win/SDL2-2.0.12")
        set(SDL2_image_DIR "dep_win/SDL2_image-2.0.5")
        set(SDL2_ttf_DIR "dep_win/SDL2_ttf-2.0.15")
        set(yaml-cpp_DIR "dep_win/yaml-cpp")

        # Link directories where libraries will be searched(when using target_link_libraries). Must be called before add_executable to have effect.
        link_directories("${SDL2_DIR}/lib/x64")
        link_directories("dep_win/SDL2_image-2.0.5/lib/x64")
        link_directories("dep_win/SDL2_ttf-2.0.15/lib/x64")
        link_directories("dep_win/yaml-cpp/lib/debug")
endif(WIN32)

# Link againts preinstalled linux libraries
if (UNIX)
add_compile_options(-g)
add_link_options(-lSDL2 -lSDL2_image -lSDL2_ttf -lyaml-cpp)
endif(UNIX)

file(GLOB core_src_files core/*.cpp)
file(GLOB src_files level_editor/*.cpp)
add_executable(LevelEditor ${src_files} ${core_src_files})
file(GLOB game_src_files game/*.cpp)
add_executable(Bounce ${game_src_files} ${core_src_files})
target_include_directories(LevelEditor PRIVATE ".")
target_include_directories(Bounce PRIVATE ".")

# Copies specified file next to the built executable
function(copy_next_to_exe file)
        add_custom_command(
                TARGET LevelEditor
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${CMAKE_SOURCE_DIR}/${file}
                        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endfunction(copy_next_to_exe file)

# Copies the specified globed files to built executable
function(copy_dir_contents_to_exe dir)
        file(GLOB files ${CMAKE_SOURCE_DIR}/${dir})
        foreach(file ${files})
                add_custom_command(
                TARGET LevelEditor
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${file}
                        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
        endforeach(file)
endfunction(copy_dir_contents_to_exe dir)

if (WIN32)
        # Add compiler include directories
        target_include_directories(LevelEditor PRIVATE "dep_win/SDL2-2.0.12/include")
        target_include_directories(LevelEditor PRIVATE "dep_win/SDL2-2.0.12/include/SDL2")
        target_include_directories(LevelEditor PRIVATE "dep_win/SDL2_image-2.0.5/include")
        target_include_directories(LevelEditor PRIVATE "dep_win/SDL2_ttf-2.0.15/include")
        target_include_directories(LevelEditor PRIVATE "dep_win/yaml-cpp/include")
	# Remove stupid duplication
	target_include_directories(Bounce PRIVATE "dep_win/SDL2-2.0.12/include")
        target_include_directories(Bounce PRIVATE "dep_win/SDL2-2.0.12/include/SDL2")
        target_include_directories(Bounce PRIVATE "dep_win/SDL2_image-2.0.5/include")
        target_include_directories(Bounce PRIVATE "dep_win/SDL2_ttf-2.0.15/include")
        target_include_directories(Bounce PRIVATE "dep_win/yaml-cpp/include")

        # Link these libraries
        target_link_libraries(LevelEditor SDL2)
        target_link_libraries(LevelEditor SDL2main)
        target_link_libraries(LevelEditor SDL2_image)
        target_link_libraries(LevelEditor SDL2_ttf)
        target_link_libraries(LevelEditor libyaml-cppmdd)
	# Remove stupid duplication
	target_link_libraries(Bounce SDL2)
        target_link_libraries(Bounce SDL2main)
        target_link_libraries(Bounce SDL2_image)
        target_link_libraries(Bounce SDL2_ttf)
        target_link_libraries(Bounce libyaml-cppmdd)


        # Copy SDL2.dll next to executable
        copy_next_to_exe(dep_win/SDL2-2.0.12/lib/x64/SDL2.dll)
        # Copy SDL2_image dll files next to executable
        copy_dir_contents_to_exe(dep_win/SDL2_image-2.0.5/lib/x64/*.dll)
        # Copy SDL2_ttf dll files next to executable
        copy_dir_contents_to_exe(dep_win/SDL2_ttf-2.0.15/lib/x64/*.dll)
endif(WIN32)   

copy_next_to_exe(resource/OpenSans-Bold.ttf)
copy_dir_contents_to_exe(resource/*.png)
copy_next_to_exe(level.yaml)

