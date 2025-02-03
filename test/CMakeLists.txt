add_executable(aboba
  test.h
  test.cpp
)

target_include_directories(aboba
  PRIVATE
    ${CMAKE_SOURCE_DIR}
)