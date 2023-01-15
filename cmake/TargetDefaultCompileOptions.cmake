string (TOUPPER ${PROJECT_NAME} PROJECT_OPTION_PREFIX)

# All options provided through this file.
option (${PROJECT_OPTION_PREFIX}_ENABLE_MOST_WARNINGS "Enable most warnings" OFF)
option (${PROJECT_OPTION_PREFIX}_ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option (${PROJECT_OPTION_PREFIX}_ENABLE_GLIBCXX_DEBUG_CHECKS "Enable GLIBCXX assertions or (for debug configuration) debug checks" ON)
option (${PROJECT_OPTION_PREFIX}_ENABLE_ASAN "(MSVC/GCC/Clang) Enable ASan" OFF)
option (${PROJECT_OPTION_PREFIX}_ENABLE_UBSAN "(GCC/Clang) Enable UBSan" OFF)
option (${PROJECT_OPTION_PREFIX}_LD_EXTEND_STACK "(Experimental) Extend stack memory to 10MB (Linux LD)" OFF)
option (${PROJECT_OPTION_PREFIX}_MACOS_LD_EXTEND_STACK "(Experimental) Extend stack memory to 10MB (macOS LD)" OFF)
option (${PROJECT_OPTION_PREFIX}_LINK_EXTEND_STACK "(Experimental) Extend stack memory to 10MB (MSVC LINK)" OFF)
option (${PROJECT_OPTION_PREFIX}_ENABLE_IPO "Enable inter-procedural (link-time) optimizations" OFF)

# See: https://cliutils.gitlab.io/modern-cmake/chapters/features/small.html
include (CheckIPOSupported)
check_ipo_supported (RESULT IPO_SUPPORTED)

# Sets default compile options for target.
# Currently supports g++/clang/cl.
function (target_default_compile_options TARGET)
  target_compile_features       (${TARGET} PRIVATE cxx_std_23)
  set_target_properties         (${TARGET} PROPERTIES CXX_EXTENSIONS OFF)

  # Basic options.
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options      (${TARGET} PRIVATE "/MP" "/EHsc")
  endif ()

  # Warnings.
  if (${PROJECT_OPTION_PREFIX}_ENABLE_MOST_WARNINGS)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      target_compile_options    (${TARGET} PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-Wdeprecated" "-Wconversion" "-Wsign-conversion" "-Werror=old-style-cast")
      target_compile_options    (${TARGET} PRIVATE "-Wno-nested-anon-types")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      target_compile_options    (${TARGET} PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-Wdeprecated" "-Wconversion" "-Wsign-conversion" "-Werror=old-style-cast")
      target_compile_options    (${TARGET} PRIVATE "-Wno-nested-anon-types")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
      target_compile_options    (${TARGET} PRIVATE "/W4" "/permissive-")
    else()
      message                   (AUTHOR_WARNING "No compiler warnings set for compiler '${CMAKE_CXX_COMPILER_ID}'.")
    endif ()
  endif ()

  # Warnings as errors.
  if (${PROJECT_OPTION_PREFIX}_ENABLE_WARNINGS_AS_ERRORS)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      target_compile_options    (${TARGET} PRIVATE "-Werror")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      target_compile_options    (${TARGET} PRIVATE "-Werror")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
      target_compile_options    (${TARGET} PRIVATE "/WX")
    else()
      message                   (AUTHOR_WARNING "Warnings-as-errors not enabled for compiler '${CMAKE_CXX_COMPILER_ID}'.")
    endif ()
  endif ()

  # Standard library debug checks.
  if (${PROJECT_OPTION_PREFIX}_ENABLE_GLIBCXX_DEBUG_CHECKS)
    target_compile_definitions  (${TARGET} PRIVATE "_GLIBCXX_ASSERTIONS")
    target_compile_definitions  (${TARGET} PRIVATE "_GLIBCXX_CONCEPT_CHECKS")
    target_compile_definitions  (${TARGET} PRIVATE "$<$<CONFIG:Debug>:_GLIBCXX_DEBUG>")
    target_compile_definitions  (${TARGET} PRIVATE "$<$<CONFIG:Debug>:_GLIBCXX_DEBUG_PEDANTIC>")
  endif ()

  # ASan.
  if (${PROJECT_OPTION_PREFIX}_ENABLE_ASAN)
    target_compile_options      (${TARGET} PRIVATE "-fsanitize=address")
    target_link_options         (${TARGET} PRIVATE "-fsanitize=address")
  endif ()

  # UBSan.
  if (${PROJECT_OPTION_PREFIX}_ENABLE_UBSAN)
    target_compile_options      (${TARGET} PRIVATE "-fsanitize=undefined")
    target_link_options         (${TARGET} PRIVATE "-fsanitize=undefined")
  endif ()

  # Extend stack memory.
  if (${PROJECT_OPTION_PREFIX}_LD_EXTEND_STACK)
    set_target_properties       (${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,stack-size=10000000")
  elseif (${PROJECT_OPTION_PREFIX}_MACOS_LD_EXTEND_STACK)
    set_target_properties       (${TARGET} PROPERTIES LINK_FLAGS "-Wl,-stack_size,10000000")
  elseif (${PROJECT_OPTION_PREFIX}_LINK_EXTEND_STACK)
    set_target_properties       (${TARGET} PROPERTIES LINK_FLAGS "/STACK:10000000")
  endif ()

  # Inter-procedural (link-time) optimisations.
  if (IPO_SUPPORTED AND ${PROJECT_OPTION_PREFIX}_ENABLE_IPO)
    set_target_properties       (${TARGET} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif ()
endfunction ()
