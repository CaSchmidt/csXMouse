cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

### Project ##################################################################

project(csXMouse)

add_subdirectory(../Win32/Win32
  ${CMAKE_CURRENT_BINARY_DIR}/Win32
  )

### Project Win32 ############################################################

list(APPEND csXMouse_HEADERS
  include/XMouse.h
  )

list(APPEND csXMouse_SOURCES
  src/main.cpp
  src/XMouse.cpp
  )

list(APPEND csXMouse_RESOURCES
  resource/XMouse.rc
  resource/XMouseRes.h
  )

add_executable(csXMouse
  ${csXMouse_HEADERS}
  ${csXMouse_SOURCES}
  ${csXMouse_RESOURCES}
  )

set_target_properties(csXMouse
  PROPERTIES WIN32_EXECUTABLE ON
  )

target_include_directories(csXMouse
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/resource
  )

target_link_libraries(csXMouse Win32)
