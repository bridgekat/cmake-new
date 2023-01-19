cmake_minimum_required (VERSION 3.15)

# ***** Edit for project.
project (
  ProjectName
  VERSION       0.1.0
  DESCRIPTION   ""
  HOMEPAGE_URL  ""
  LANGUAGES     CXX
)

# ***** Edit to match the directory of `prelude`.
list (PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/extern/prelude/cmake")
include (Prelude NO_POLICY_SCOPE)

# ===== Dependencies =====

# ===== Targets =====
add_library (mylib OBJECT
  src/mylib.cpp)
target_default_compile_options  (mylib)
target_include_directories      (mylib PRIVATE src PUBLIC include)

# ===== Tests =====
enable_testing ()

add_executable (mytest
  tests/mytest.cpp)
target_default_compile_options  (mytest)
target_include_directories      (mytest PRIVATE src include)
target_link_libraries           (mytest PRIVATE mylib)
add_test                        (mytest mytest)
