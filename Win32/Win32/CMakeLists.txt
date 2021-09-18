cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

### Project ##################################################################

project(Win32)

### Win32 ####################################################################

list(APPEND Win32_HEADERS
  include/Win32/CheckBox.h
  include/Win32/DialogBase.h
  include/Win32/SysParam.h
  include/Win32/Types.h
  include/Win32/Window.h
  )

list(APPEND Win32_SOURCES
  src/CheckBox.cpp
  src/DialogBase.cpp
  src/SysParam.cpp
  src/Window.cpp
  )

list(APPEND Win32_RESOURCES
  resource/DialogBaseRes.h
  )

add_library(Win32 STATIC
  ${Win32_HEADERS}
  ${Win32_SOURCES}
  ${Win32_RESOURCES}
  )

target_compile_definitions(Win32
  PUBLIC UNICODE
  )

target_include_directories(Win32
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/resource
  )

target_link_libraries(Win32)

### Examples #################################################################

add_executable(example_DialogBase
  examples/example_DialogBase.cpp
  resource/DialogBase.rc
  )

set_target_properties(example_DialogBase
  PROPERTIES
  WIN32_EXECUTABLE ON
  )

target_link_libraries(example_DialogBase Win32)
