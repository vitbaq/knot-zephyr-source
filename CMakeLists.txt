cmake_minimum_required(VERSION 3.8.2)
find_package(Git REQUIRED)

macro(set_conf_file)
  if(EXISTS ${APPLICATION_SOURCE_DIR}/prj_${BOARD}.conf)
    set(CONF_FILE "${APPLICATION_SOURCE_DIR}/prj_${BOARD}.conf")
  elseif(EXISTS ${APPLICATION_SOURCE_DIR}/boards/${BOARD}.conf)
    set(CONF_FILE
      "prj.conf ${APPLICATION_SOURCE_DIR}/boards/${BOARD}.conf")
  else()
    set(CONF_FILE "prj.conf")
  endif()
endmacro()

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)

include(ExternalProject)

zephyr_get_include_directories_for_lang_as_string(C includes)
zephyr_get_system_include_directories_for_lang_as_string(C system_includes)
zephyr_get_compile_options_for_lang_as_string(C c_options)

set(PROTO_ROOT ${CMAKE_CURRENT_LIST_DIR}/external/proto)
set(PROTO_LIB_DIR ${PROTO_ROOT}/lib)
set(PROTO_INCLUDE_DIR ${PROTO_ROOT}/include)
set(PROTO_LIB knotprotocol)

set(configure_flags
  "CC=${CMAKE_C_COMPILER}"
  "RANLIB=${CMAKE_RANLIB}"
  "CFLAGS=${c_options} ${includes} ${system_includes}"
  "LDFLAGS=-nostdlib"# Don't use the standard system startup files or libraries
  --host=${CROSS_COMPILE_TARGET}
  --target=${CROSS_COMPILE_TARGET}
  --prefix=${PROTO_ROOT}
)

add_library(${PROTO_LIB} STATIC IMPORTED GLOBAL)

set_target_properties(${PROTO_LIB} PROPERTIES IMPORTED_LOCATION
    ${PROTO_LIB_DIR}/lib${PROTO_LIB}.a
)

target_include_directories(app SYSTEM PRIVATE ${PROTO_INCLUDE_DIR})

target_link_libraries(app INTERFACE ${PROTO_LIB})

ExternalProject_Add(proto
    PREFIX ${PROTO_ROOT}
    BINARY_DIR ${PROTO_ROOT}/src/proto
    SOURCE_DIR ${PROTO_ROOT}/src/proto
    GIT_REPOSITORY https://github.com/CESARBR/knot-protocol-source.git
    BUILD_BYPRODUCTS ${PROTO_LIB_DIR}/lib${PROTO_LIB}.a
    CONFIGURE_COMMAND ./bootstrap && ./configure ${configure_flags}

    COMMENT "bootstrapping..." # Text printed when step executes
    BUILD_COMMAND make
)

project(knot_hello_world)

add_dependencies(app proto)
FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

include($ENV{ZEPHYR_BASE}/samples/net/common/common.cmake)
