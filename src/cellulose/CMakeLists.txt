add_executable(cellulose
    main.cc
)
target_link_libraries(cellulose ${glove_libs})

if(WIN32)
	add_custom_command(TARGET cellulose POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${deps_path}/shared"
        $<TARGET_FILE_DIR:cellulose>)
endif()

add_custom_command(TARGET cellulose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/../data"
    $<TARGET_FILE_DIR:cellulose>/data)

add_custom_command(TARGET cellulose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/../python"
    $<TARGET_FILE_DIR:cellulose>/data/python)

add_custom_command(TARGET cellulose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:mod_glrenderer>
    $<TARGET_FILE_DIR:cellulose>/data/natex/$<TARGET_FILE_NAME:mod_glrenderer>)