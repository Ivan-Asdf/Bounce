#link_directories("CMAKE_LIBRARY_OUTPUT_DIRECTORY")
add_executable(LevelEditor main_level_editor.cpp)
add_executable(Bounce main_game.cpp)
target_link_libraries(Bounce Game_lib)
target_link_libraries(LevelEditor LevelEditor_lib)

if (WIN32)
    target_include_directories(LevelEditor
                            PRIVATE "${SDL2_DIR}/include"
                            PRIVATE "${SDL2_DIR}/include/SDL2"
                            PRIVATE "${SDL2_image_DIR}/include"
                            PRIVATE "${SDL2_ttf_DIR}/include"
                            PRIVATE "${cpp_DIR}/include")

    target_link_libraries(LevelEditor SDL2 SDL2main SDL2_image SDL2_ttf libyaml-cppmdd)

    target_include_directories(Bounce
                            PRIVATE "${SDL2_DIR}/include"
                            PRIVATE "${SDL2_DIR}/include/SDL2"
                            PRIVATE "${SDL2_image_DIR}/include"
                            PRIVATE "${SDL2_ttf_DIR}/include"
                            PRIVATE "${cpp_DIR}/include")

    target_link_libraries(Bounce SDL2 SDL2main SDL2_image SDL2_ttf libyaml-cppmdd)

    # message(${CMAKE_CURRENT_BINARY_DIR})
    # message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    # message(${CMAKE_SOURCE_DIR})

    # file(GLOB dll_files ${CMAKE_SOURCE_DIR}/lib/win/SDL2_image-2.0.5/lib/x64/*.dll)
    # message(${dll_files})
    # foreach()
        
    # endforeach()

    # Custom command to copy all DLL dependencies on Windows next to the executable.
    add_custom_command(
    OUTPUT
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/SDL2.dll  
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/*.dll
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/lib/win/SDL2-2.0.12/lib/x64/SDL2.dll
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/lib/win/SDL2_image-2.0.5/lib/x64/*.dll
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/lib/win/SDL2_ttf-2.0.15/lib/x64/*.dll
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMENT "Copying windows DLLs next to executable"
    )
    # Can be improved to detect if one of ddls has been deleted next to exe and then copy again.
    # But not worth the work. The commented code above is me starting doing that.

    add_custom_target(DLL
        ALL
        DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/*.dll
    )
endif(WIN32)

# Copy all resources next to the executable
add_custom_command(
    OUTPUT  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/ball.png
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/resource/*
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMENT "Resource target(copy resources next to executables)"
)

add_custom_target(Resources
    ALL
    DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/ball.png
)
