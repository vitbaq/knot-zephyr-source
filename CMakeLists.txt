cmake_minimum_required(VERSION 3.8.2)
find_package(Git REQUIRED)

include(ExternalProject)

set(ep_base ${CMAKE_CURRENT_LIST_DIR}/build/proto)
set_property(DIRECTORY PROPERTY "EP_BASE" ${ep_base})

ExternalProject_Add(proto
    GIT_REPOSITORY https://github.com/CESARBR/knot-protocol-source.git
)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(knot_hello_world)
add_dependencies(app proto)
target_sources(app PRIVATE src/main.c)
