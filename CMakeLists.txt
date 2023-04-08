cmake_minimum_required(VERSION 3.24)
project(SandBox)
set(SDIR SandBox/src/)
add_executable(
    ${PROJECT_NAME} 
    ${SDIR}main.cpp)