cmake_minimum_required(VERSION 3.24)
project(SandBox)
set(CMAKE_CXX_STANDARD 23)
set(SDIR SandBox/src/)
add_executable(
    ${PROJECT_NAME} 
    ${SDIR}main.cpp
        XoX/src/ecs/ecs.ixx XoX/src/template/Delegata/delegata.ixx XoX/src/template/template.ixx)

add_library(lib SHARED XoX)
target_include_directories(XoX PUBLIC XoX/src/)