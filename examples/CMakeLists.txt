cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(ce-examples CXX)
include(cmake/StandardProjectSettings.cmake)
set (CMAKE_CXX_STANDARD 20)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
option(ENABLE_TESTING "Enable Test Builds" ON)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which
  # is a good idea if any #define's change
  target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

include_directories(../include)
add_executable(examples example.cpp)
add_executable(bench benchmarks.cpp nanobench.o)


find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(examples PRIVATE project_options project_warnings Eigen3::Eigen)
target_link_libraries(bench PRIVATE project_options project_warnings Eigen3::Eigen)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(examples PRIVATE -Ofast -fconcepts-ts)
  target_compile_options(bench PRIVATE -O3 -fconcepts-ts)
endif ()
