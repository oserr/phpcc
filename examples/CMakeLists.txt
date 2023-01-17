add_executable(main main.cc)
target_include_directories(main PRIVATE ${phpcc_project_dir})
target_link_libraries(main PRIVATE phpcc)
target_compile_features(main PUBLIC cxx_std_20)
