cmake_minimum_required(VERSION 3.12)

# cmake

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# project

project(roq-cpp-algo-template)

# conda

if(DEFINED ENV{CONDA_PREFIX} AND NOT DEFINED ENV{CONDA_BUILD})
  set(CMAKE_INSTALL_PREFIX $ENV{CONDA_PREFIX})
  set(CMAKE_FIND_ROOT_PATH $ENV{CONDA_PREFIX})
endif()

# rpath

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# c++

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

# filesystem

include(GNUInstallDirs)

# dependencies

find_package(absl REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(
  Python
  COMPONENTS Interpreter Development
  REQUIRED)
find_package(roq-algo REQUIRED)
find_package(roq-api REQUIRED)
find_package(roq-cache REQUIRED)
find_package(roq-client REQUIRED)
find_package(roq-codec REQUIRED)
find_package(roq-fix REQUIRED)
find_package(roq-flags REQUIRED)
find_package(roq-io REQUIRED)
find_package(roq-logging REQUIRED)
find_package(roq-market REQUIRED)
find_package(roq-python-core REQUIRED)
find_package(roq-utils REQUIRED)
find_package(tomlplusplus REQUIRED)
find_package(unordered_dense REQUIRED)

# find python's site-packages https://stackoverflow.com/a/40006251

message(PYTHON_EXECUTABLE="${PYTHON_EXECUTABLE}")

execute_process(
  COMMAND "${PYTHON_EXECUTABLE}" -c "from distutils import sysconfig as sc; print(sc.get_python_lib(prefix='', plat_specific=True))"
  OUTPUT_VARIABLE PYTHON_SITE
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# autogen

find_program(ROQ_AUTOGEN roq-autogen REQUIRED)

set(TEMPLATE_DIR ${CMAKE_SOURCE_DIR}/scripts/templates)

# clang-format

find_program(CLANG_FORMAT clang-format REQUIRED)

# include

include_directories(
  ${CMAKE_SOURCE_DIR}/src
  # >>> autogen >>>
  ${CMAKE_BINARY_DIR}/src)

# sub-projects

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/roq/samples/algo)

# test

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

find_package(Catch2 REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/test)

# benchmark

find_package(benchmark REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/benchmark)
