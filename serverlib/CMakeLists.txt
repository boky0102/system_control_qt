cmake_minimum_required(VERSION 3.16)

project(serverlib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(serverlib SHARED
  serverlib_global.h
  serverlib.cpp
  serverlib.h
)

target_compile_definitions(serverlib PRIVATE SERVERLIB_LIBRARY)
