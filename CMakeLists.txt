cmake_minimum_required(VERSION 3.11)

project(hello-lua VERSION 0.0.1 LANGUAGES C CXX)

include(FetchContent)

find_package(Lua REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(openv2g)

#
# parser library
#
add_library(openv2g_parser)

target_include_directories(openv2g_parser
    PUBLIC
        src
)

target_sources(openv2g_parser
    PRIVATE
        src/v2g.cpp
        src/messages.cpp
        src/helpers.cpp
)

target_link_libraries(openv2g_parser
    PRIVATE
        fmt::fmt
        openv2g_codec 
)

#
# wireshark plugin
#
add_library(openv2g_parser_lua SHARED)

set_target_properties(openv2g_parser_lua PROPERTIES PREFIX "")
target_include_directories(openv2g_parser_lua PRIVATE ${LUA_INCLUDE_DIR})

target_sources(openv2g_parser_lua
    PRIVATE
        wireshark/openv2g_parser_lua.cpp
)


target_link_libraries(openv2g_parser_lua
    PRIVATE
        ${LUA_LIBRARIES}
        openv2g_parser 
)

