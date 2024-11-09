set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(flags)
add_subdirectory(impl)

set(SOURCES application.cpp config.cpp factory.cpp settings.cpp main.cpp)

add_executable(${TARGET_NAME} ${SOURCES})

add_dependencies(${TARGET_NAME} ${TARGET_NAME}-flags-autogen-headers)

target_link_libraries(
  ${TARGET_NAME}
  PRIVATE ${TARGET_NAME}-flags
          ${PROJECT_NAME}-impl
          roq-client::roq-client
          roq-client::roq-client-flags
          roq-algo::roq-algo
          roq-cache::roq-cache
          roq-market::roq-market
          roq-logging::roq-logging
          roq-logging::roq-logging-flags
          roq-flags::roq-flags
          roq-api::roq-api
          tomlplusplus::tomlplusplus
          unordered_dense::unordered_dense
          fmt::fmt)

if(ROQ_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)
endif()

target_compile_definitions(${TARGET_NAME} PRIVATE ROQ_PACKAGE_NAME="${PROJECT_NAME}")

install(TARGETS ${TARGET_NAME})

# python

set(PYTHON_TARGET_NAME ${PROJECT_NAME}-python)

set(PYTHON_SOURCES module.cpp)

pybind11_add_module(${PYTHON_TARGET_NAME} ${PYTHON_SOURCES})

target_link_libraries(
  ${PYTHON_TARGET_NAME}
  PUBLIC pybind11::headers
  PRIVATE ${PROJECT_NAME}-impl roq-python-core::roq-python-core roq-algo::roq-algo fmt::fmt)

# note! python packages are not allowed to use "-" (dash) in their name
string(REPLACE "-" "_" PYTHON_PROJECT_NAME ${PROJECT_NAME}) # note! using PROJECT_NAME
set_target_properties(${PYTHON_TARGET_NAME} PROPERTIES OUTPUT_NAME ${PYTHON_PROJECT_NAME})
target_compile_definitions(${PYTHON_TARGET_NAME} PRIVATE ROQ_PACKAGE_NAME=${PYTHON_PROJECT_NAME})

install(TARGETS ${PYTHON_TARGET_NAME} DESTINATION ${PYTHON_SITE}/${PYTHON_PROJECT_NAME})
