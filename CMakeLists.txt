cmake_minimum_required(VERSION 3.9.0)
project(datastructures VERSION 0.1.0 LANGUAGES C)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-ffunction-sections -fdata-sections)
endif()

add_library(datastructures ${CMAKE_CURRENT_SOURCE_DIR}/src/heap.c)

target_include_directories(datastructures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

option(example "Build examples" ON)

if(example)
add_executable(example_heap ${CMAKE_CURRENT_SOURCE_DIR}/example/heap.c)
target_link_libraries(example_heap datastructures)
target_include_directories(example_heap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
option(example_asan "ASAN" OFF)
if(example_asan)
target_compile_options(example_heap PRIVATE -fsanitize=address,undefined)
target_link_options(example_heap PRIVATE -fsanitize=address,undefined)
endif()
endif()

include(CheckIPOSupported)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_link_options(datastructures PRIVATE -Wl,--gc-sections)
endif()

check_ipo_supported(RESULT result OUTPUT output LANGUAGES C)
if(result)
message(STATUS "IPO is supported")
set_property(TARGET datastructures PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
message(WARNING "IPO is not supported: ${output}")
endif()
