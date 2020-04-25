
file(GLOB level_editor_src_files *.cpp)
add_library(LevelEditor_lib ${level_editor_src_files})
target_include_directories(LevelEditor_lib PUBLIC "..")
target_link_libraries(LevelEditor_lib Core_lib)