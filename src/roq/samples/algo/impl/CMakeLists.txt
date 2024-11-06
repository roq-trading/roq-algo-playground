set(TARGET_NAME ${PROJECT_NAME}-impl)

set(SOURCES instrument.cpp strategy.cpp)

add_library(${TARGET_NAME} OBJECT ${SOURCES})

target_link_libraries(${TARGET_NAME} roq-algo::roq-algo)
