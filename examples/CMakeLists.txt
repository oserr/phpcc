include_directories(${CMAKE_SOURCE_DIR})
add_executable(main main.cc)
target_link_libraries(main PRIVATE phpcc)
target_compile_features(main PUBLIC cxx_std_20)
