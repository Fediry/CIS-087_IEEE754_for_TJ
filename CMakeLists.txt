cmake_minimum_required(VERSION 3.21)

# Config
project(IEEE754_For_TJ VERSION 0.1.0 LANGUAGES C CXX)

# Sources
set(SOURCES
src/main.cpp
src/ieee754.cpp
src/tests.cpp
)
set(HEADERS
inc/main.h
inc/ieee754.h
inc/tests.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)

# Options
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-DDEBUG>)