string(REPLACE "lib/cmake/qualla" "" _qualla_prefix ${CMAKE_CURRENT_LIST_DIR})
set(_qualla_include_dir ${_qualla_prefix}/include)
set(_qualla_library_dir ${_qualla_prefix}/lib)

if(TARGET qualla)
    return()
endif()

add_library(qualla INTERFACE IMPORTED)
target_include_directories(qualla INTERFACE ${_qualla_include_dir})
target_link_libraries(qualla INTERFACE ${_qualla_library_dir}/libqualla.so.1)

set(QUALLA_VERSION "1.0.2")
set(QUALLA_LIBRARIES qualla)

message(STATUS "QUALLA version: ${QUALLA_VERSION}   : ${_qualla_prefix}")
