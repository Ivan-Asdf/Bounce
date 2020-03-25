cmake_minimum_required(VERSION 3.10)

project(Bounce)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

link_directories("dep_win/SDL2-2.0.12/lib/x64")

add_executable(Bounce main.cpp level_editor.h)

target_include_directories(Bounce PRIVATE "dep_win/SDL2-2.0.12/include")

target_link_libraries(Bounce SDL2)
target_link_libraries(Bounce SDL2main)

add_custom_command(
        TARGET Bounce
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/dep_win/SDL2-2.0.12/lib/x64/SDL2.dll
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)




