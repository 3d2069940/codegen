function(codegen_generate TARGET_NAME GENERATED_FILES GENERATED_DIRS)
  set(GENERATED_FILES)
  set(GENERATED_DIRS)

  get_target_property(TARGET_SOURCE_FILES ${TARGET_NAME} SOURCES)

  if (NOT TARGET_SOURCE_FILES)
    message(FATAL_ERROR "Target '${TARGET_NAME}' doesn't exist or has no sources. Bruh")
  endif()

  foreach(TARGET_SOURCE_FILE ${TARGET_SOURCE_FILES})
    file(RELATIVE_PATH TARGET_FILE_RELATIVE_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_SOURCE_FILE})

    set(TARGET_GENERATED_FILES)
    execute_process(
      COMMAND           ${CODEGENERATOR_EXEC} -p ${CMAKE_BINARY_DIR}
                                              --relative-path=${TARGET_FILE_RELATIVE_PATH}
                                              ${TARGET_FILE_RELATIVE_PATH}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE   TARGET_GENERATED_FILES
      ERROR_VARIABLE    DUMMY
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    list(APPEND GENERATED_FILES ${TARGET_GENERATED_FILES})
  endforeach()
endfunction()