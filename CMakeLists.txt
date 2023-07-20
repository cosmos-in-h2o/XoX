cmake_minimum_required(VERSION 3.15.0)
set(CMAKE_CXX_STANDARD 23)
project(XoX LANGUAGES CXX C)

file(GLOB_RECURSE MODULE ./*.ixx)
file(GLOB_RECURSE SOURCE ./*.cc)
add_executable(XoX)
target_include_directories(XoX PRIVATE
    include
    thirdparty/include
)
add_definitions(-DXOX_EXPORT)

target_sources(XoX PRIVATE
        ${MODULE}
        ${SOURCE}
        )