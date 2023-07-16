cmake_minimum_required(VERSION 3.25)
project(XoX LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

#主要库
add_library(XoX SHARED)
#SandBox
add_executable(SandBox)
#文件列表
file(GLOB_RECURSE XoX_Module "XoX/module/*.ixx")
file(GLOB_RECURSE XoX_Source "XoX/src/*.cc")
file(GLOB_RECURSE SandBox_Source "SandBox/src/*.cc")
#项目属性
set_target_properties(XoX
        PROPERTIES OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION})
#XoX的源文件，不向下传递模块文件，原因不单独给SandBox模块文件目录不同会报错
target_sources(XoX
        PRIVATE ${XoX_Module} ${XoX_Source})
#XoX的include目录，并向下传递
target_include_directories(XoX
        PUBLIC XoX/include/)
#XoX的definitions，明确这时是在导出，不能向下传递
target_compile_definitions(XoX
        PRIVATE -DXOX_EXPORT)

#SandBox源文件，以及需要的模块接口
target_sources(SandBox
        PRIVATE ${SandBox_Source} #${XoX_Module}
        )
##依赖
#target_link_libraries(SandBox
#        PRIVATE XoX)