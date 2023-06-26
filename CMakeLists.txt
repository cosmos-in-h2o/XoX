cmake_minimum_required(VERSION 3.25)
project(XoX)

set(CMAKE_CXX_STANDARD 20)

add_executable(XoX XoX/module/xox.ixx
        XoX/module/memory/memory.ixx
        XoX/src/stack_pool.cc XoX/module/log.ixx
        XoX/module/memory/stack_pool.ixx
        XoX/module/memory/smart_stack_pool.ixx
        XoX/src/smart_stack_pool.cc
        XoX/module/delegate.ixx SandBox/src/main.cc)
