

file(GLOB game_src_files *.cpp)
add_library(Game_lib ${game_src_files})
target_link_libraries(Game_lib Core_lib)
target_include_directories(Game_lib PUBLIC "..")