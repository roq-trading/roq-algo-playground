set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(flags)

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
