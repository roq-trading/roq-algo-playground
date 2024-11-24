set(TARGET_NAME ${PROJECT_NAME}-strategy)

set(SOURCES arbitrage.cpp factory.cpp instrument.cpp)

add_library(${TARGET_NAME} OBJECT ${SOURCES})

target_link_libraries(${TARGET_NAME} PRIVATE roq-algo::roq-algo roq-logging::roq-logging)
