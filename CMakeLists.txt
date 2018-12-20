cmake_minimum_required(VERSION 3.8.2)
find_package(Git REQUIRED)

set(PROTO_ROOT ${CMAKE_BINARY_DIR}/external/proto)
set(PROTO_LIB_DIR ${PROTO_ROOT}/bin/lib)
set(PROTO_INCLUDE_DIR ${PROTO_ROOT}/bin/include)

include(ExternalProject)

ExternalProject_Add(proto
    PREFIX ${PROTO_ROOT}
    GIT_REPOSITORY https://github.com/CESARBR/knot-protocol-source.git
    BINARY_DIR ${PROTO_ROOT}/src/proto
    SOURCE_DIR ${PROTO_ROOT}/src/proto
    CONFIGURE_COMMAND "./bootstrap-configure"
    BUILD_COMMAND make
)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(knot_hello_world)
add_dependencies(app proto)
target_sources(app PRIVATE src/main.c)
