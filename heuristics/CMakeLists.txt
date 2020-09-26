cmake_minimum_required(VERSION 2.8.11)

project(cubed)

find_package(PkgConfig)

pkg_check_modules(GLIB REQUIRED glib-2.0)

set(CMAKE_C_COMPILER gcc)

set(FLAGS "-std=c99 -I . -pthread -pipe -Wall -Wextra -Wno-system-headers")
set(FLAGS "${FLAGS} -Wno-padded -fdiagnostics-color=always")

set(DEBUG_FLAGS "${FLAGS} -g -ggdb3 -O0 -fno-omit-frame-pointer -fno-common -fstrict-aliasing")
set(OPTMISING_FLAGS "${FLAGS} -O3 -march=native -DNDEBUG -flto ")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_executable(cubed
    bitset.c
    board.c
    bot.c
    control.c
    cubed.c
    testing.c
)

target_link_libraries(cubed
    ${GLIB_LIBRARIES}
)

set_target_properties(cubed PROPERTIES COMPILE_FLAGS ${OPTMISING_FLAGS})

add_executable(heuristics
    heuristics.c
    bitset.c
    board.c
    bot.c
)

set_target_properties(heuristics PROPERTIES COMPILE_FLAGS ${OPTMISING_FLAGS})

target_link_libraries(heuristics
    ${GLIB_LIBRARIES}
)
