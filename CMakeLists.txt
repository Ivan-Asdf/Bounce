cmake_minimum_required(VERSION 3.10)

project(Bounce)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Link directories where libraries will be searched(when using target_link_libraries). Must be called before add_executable to have effect.
link_directories("dep_win/SDL2-2.0.12/lib/x64")
link_directories("dep_win/SDL2_image-2.0.5/lib/x64")
link_directories("dep_win/SDL2_ttf-2.0.15/lib/x64")
link_directories("dep_win/yaml-cpp/lib/debug")

file(GLOB src_files *.cpp)
add_executable(Bounce ${src_files})

target_include_directories(Bounce PRIVATE "dep_win/SDL2-2.0.12/include")
target_include_directories(Bounce PRIVATE "dep_win/SDL2-2.0.12/include/SDL2")
target_include_directories(Bounce PRIVATE "dep_win/SDL2_image-2.0.5/include")
target_include_directories(Bounce PRIVATE "dep_win/SDL2_ttf-2.0.15/include")
target_include_directories(Bounce PRIVATE "dep_win/yaml-cpp/include")

target_link_libraries(Bounce SDL2)
target_link_libraries(Bounce SDL2main)
target_link_libraries(Bounce SDL2_image)
target_link_libraries(Bounce SDL2_ttf)
target_link_libraries(Bounce libyaml-cppmdd)

# Copy SDL2.dll next to executable
add_custom_command(
        TARGET Bounce
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/dep_win/SDL2-2.0.12/lib/x64/SDL2.dll
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)

# Copy SDL2_image dll files next to executable
file(GLOB dll_files ${CMAKE_SOURCE_DIR}/dep_win/SDL2_image-2.0.5/lib/x64/*.dll)
foreach(dll_file ${dll_files})
        add_custom_command(
        TARGET Bounce
        COMMAND ${CMAKE_COMMAND} -E copy
                ${dll_file}
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)
endforeach(dll_file)

# Copy SDL2_ttf dll files next to executable
file(GLOB dll_files ${CMAKE_SOURCE_DIR}/dep_win/SDL2_ttf-2.0.15/lib/x64/*.dll)
foreach(dll_file ${dll_files})
        add_custom_command(
        TARGET Bounce
        COMMAND ${CMAKE_COMMAND} -E copy
                ${dll_file}
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)
endforeach(dll_file)

# Copy font ttf file next to executable
add_custom_command(
        TARGET Bounce
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/OpenSans-Bold.ttf
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)

# Copy png files next to executable
file(GLOB png_files ${CMAKE_SOURCE_DIR}/*.png)
foreach(png_file ${png_files})
        add_custom_command(
        TARGET Bounce
        COMMAND ${CMAKE_COMMAND} -E copy
                ${png_file}
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)
endforeach(png_file)

# Copy level.yaml file next to executable
add_custom_command(
        TARGET Bounce
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/level.yaml
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)

