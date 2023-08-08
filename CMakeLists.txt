# !!!!仅用于补全,不能构建项目

cmake_minimum_required(VERSION 3.25)
project(XoX LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
add_executable(XoX)
#文件列表
file(GLOB_RECURSE XoX_Module ./core/*.ixx ./driver/*.ixx ./world/*.ixx)
file(GLOB_RECURSE XoX_Source ./core/*.cc ./driver/*.cc ./world/*.cc)
file(GLOB_RECURSE Editor_Source ./editor/*.cc)

target_sources(XoX
        PRIVATE ${XoX_Module} ${XoX_Source} ${Editor_Source})
#XoX的include目录，并向下传递
target_include_directories(XoX
        PUBLIC ./include/ ./thirdparty/include/)
#XoX的definitions，明确这时是在导出，不能向下传递
target_compile_definitions(XoX
        PRIVATE -DXOX_EXPORT)
