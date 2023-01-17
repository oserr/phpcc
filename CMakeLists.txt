cmake_minimum_required(VERSION 3.25)
project(phpcc CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# picohttpparser
FetchContent_Declare(
  picohttpparser
  GIT_REPOSITORY https://github.com/oserr/picohttpparser.git
  GIT_TAG 391ad78c2b9beada93a9d3de7565e34895aadc66)
FetchContent_GetProperties(picohttpparser)
if(NOT picohttpparser)
  FetchContent_Populate(picohttpparser)
  message(STATUS "picohttpparser source dir: ${picohttpparser_SOURCE_DIR}")
  message(STATUS "picohttpparser binary dir: ${picohttpparser_BINARY_DIR}")
  add_subdirectory(${picohttpparser_SOURCE_DIR} ${picohttpparser_BINARY_DIR})
endif()

set(phpcc_project_dir ${CMAKE_CURRENT_SOURCE_DIR})

add_library(phpcc 
    pico_http_request.h
    pico_http_parser.h
    pico_http_parser.cc)
target_include_directories(phpcc PRIVATE ${picohttpparser_SOURCE_DIR})
target_link_libraries(phpcc PRIVATE picohttpparser)

add_subdirectory(examples)
