cmake_minimum_required(VERSION 3.11)

project(html_paint CXX)
set(CMAKE_CXX_STANDARD 17) 

#set(SOURCE_DIR src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

file(GLOB sources
  src/main.cpp
  src/graphics.h
  src/graphics.cpp
  src/html.h
  src/html.cpp
  src/tests.h
  src/tests.cpp
  src/html_generator.h
  src/html_generator.cpp
)

add_executable(html_paint ${sources}) 

