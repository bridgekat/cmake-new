cmake_minimum_required (VERSION 3.27)
cmake_policy (SET CMP0135 NEW)

# TODO: remove in CMake 3.28
set (CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set (CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

# TODO: edit for project.
project (the_project_name
  VERSION       0.1.0
  DESCRIPTION   ""
  HOMEPAGE_URL  ""
  LANGUAGES     CXX
)

# ===== Scripts =====
list (PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include (FetchContent)
include (TargetDefaultCompileOptions)
include (CppcheckCodeAnalysis)

# ===== Dependencies =====

# ===== Targets =====
add_library (the_project_name)
target_sources (the_project_name
  PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
  "src/the_project_name.cpp"
)
target_default_compile_options (the_project_name)

add_executable (simple_test tests/simple_test.cpp)
target_link_libraries (simple_test PRIVATE the_project_name)
target_default_compile_options (simple_test)

# ===== Tests =====
enable_testing ()
add_test (simple_test simple_test)
