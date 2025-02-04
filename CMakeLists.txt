cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(CodeGenerator VERSION 0.0.1)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

execute_process(
  COMMAND llvm-config --cxxflags
  OUTPUT_VARIABLE LLVM_CXX_FLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
  COMMAND llvm-config --ldflags
  OUTPUT_VARIABLE LLVM_LDFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
  COMMAND llvm-config --libs
  OUTPUT_VARIABLE LLVM_LIBRARIES
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
  COMMAND llvm-config --system-libs
  OUTPUT_VARIABLE LLVM_SYSTEM_LIBRARIES
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LDFLAGS}")
set(CLANG_LIBS
  clangTooling 
  clangFrontendTool 
  clangFrontend 
  clangDriver 
  clangSerialization 
  clangCodeGen 
  clangParse
  clangSema
  clangStaticAnalyzerFrontend
  clangStaticAnalyzerCheckers
  clangStaticAnalyzerCore
  clangAnalysis
  clangARCMigrate
  clangRewrite
  clangRewriteFrontend
  clangEdit
  clangAST
  clangLex
  clangBasic
  clang
)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_executable(${PROJECT_NAME}
  src/main.cpp

  src/common/common.hpp

  src/visitor/visitor.cpp
  src/visitor/visitor.hpp

  src/consumer/consumer.hpp
  src/consumer/consumer.cpp

  src/generator/generator.hpp
  src/generator/generator.cpp

  src/frontendAction/structFrontendAction.cpp
  src/frontendAction/structFrontendAction.hpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CLANG_INCLUDE_DIRS}
)
target_link_directories(${PROJECT_NAME} 
  PRIVATE 
    /usr/local/lib
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${CLANG_LIBS}
    ${LLVM_LIBRARIES}
    ${LLVM_SYSTEM_LIBRARIES}
)

add_subdirectory(test)

install(TARGETS CodeGenerator
        RUNTIME DESTINATION bin
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  cmake/CodeGeneratorConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/CodeGeneratorConfig.cmake"
  INSTALL_DESTINATION lib/cmake/CodeGenerator
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/CodeGeneratorConfig.cmake"
  DESTINATION lib/cmake/CodeGenerator
)
install(FILES
  "${CMAKE_SOURCE_DIR}/cmake/generator.cmake"
  DESTINATION lib/cmake/CodeGenerator
)