cmake_minimum_required(VERSION 3.11)

project(html_paint CXX)
set(CMAKE_CXX_STANDARD 17) 

#set(SOURCE_DIR src)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

file(GLOB sources
  #${SOURCE_DIR}/*.cpp
  #${SOURCE_DIR}/*.h
  src/main.cpp
  src/graphics.h
  src/graphics.cpp
  src/html.h
  src/html.cpp
  src/tests.h
  src/tests.cpp
)

add_executable(html_paint ${sources}) 

