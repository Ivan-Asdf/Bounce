file(GLOB core_src_files *.cpp)
add_library(Core_lib ${core_src_files})
target_include_directories(Core_lib PUBLIC ".")