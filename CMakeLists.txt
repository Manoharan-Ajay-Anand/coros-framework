cmake_minimum_required(VERSION 3.1)

project(Coros
    VERSION 1.0
    DESCRIPTION "Coros Framework"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")

add_subdirectory(libraries/coros)
add_subdirectory(libraries/coros-fcgi)

add_executable(echo examples/echo.cpp)
target_link_libraries(echo PRIVATE coros)

add_executable(hello examples/hello.cpp)
target_link_libraries(hello PRIVATE coros)
target_link_libraries(hello PRIVATE coros-fcgi)
