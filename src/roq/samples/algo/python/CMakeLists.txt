# set(TARGET_NAME ${PROJECT_NAME}-python)
set(TARGET_NAME playground)

set(SOURCES main.cpp)

pybind11_add_module(${TARGET_NAME} ${SOURCES})

target_link_libraries(
  ${TARGET_NAME}
  PUBLIC pybind11::headers
  PRIVATE roq-algo::roq-algo)

if(ROQ_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)
endif()

target_compile_definitions(${TARGET_NAME} PRIVATE ROQ_PACKAGE_NAME="${PROJECT_NAME}")
