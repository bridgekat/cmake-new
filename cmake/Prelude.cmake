# Specify CMake behaviours to eliminate warnings.
if (POLICY CMP0135)
  cmake_policy (SET CMP0135 NEW)
endif ()

include (FetchContent)
include (CppcheckCodeAnalysis)
include (TargetDefaultCompileOptions)
