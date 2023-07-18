-- 添加模式
add_rules("mode.debug","mode.release")

-- c++23
set_languages("c++23")

-- 编译器
add_toolchains("msvc")

-- 引擎依赖项
add_requires(
    -- "entt", -- 一个高效的esc框架(MIT)(本库手动导入，在thirdparty文件夹下)
    -- "eastl", -- 一个EA实现的的适用于游戏的stl(BSD)
    -- "mimalloc" -- 一个微软实现的高效内存分配器(MIT)
)

-- 引擎主体
target("XoX")
    -- add_packages("eastl","mimalloc")
    --动态库类型
    set_kind("shared")
    -- 头文件包含
    add_includedirs("./include/")
    add_includedirs("./thirdparty/include/")
    -- 导出dll宏
    add_defines("XOX_EXPORT")
    -- 模块接口文件与源文件
    add_files("./core/**.ixx")
    add_files("./core/**.cc")
    -- 静态库文件
    add_linkdirs("./thirdparty/lib/")
    add_links("mimalloc-static")
    -- 导出目录
    set_targetdir("./target/")
    if(is_plat("windows")) then 
        set_runtimes("MD")
        add_links("Advapi32")
    end
target_end()

-- 编辑器
target("XoX-editor")
    -- 可执行文件
    set_kind("binary")
    -- 头文件包含
    add_includedirs("./include/")
    add_includedirs("./thirdparty/include/")
    -- 自身源文件
    add_files("./editor/src/**.ixx")
    add_files("./editor/src/**.cc")
    -- 引擎依赖
    add_files("./core/**.ixx")
    add_deps("XoX")
    -- 导出目录
    set_targetdir("./target/")
    if(is_plat("windows")) then
        set_runtimes("MD")
    end
target_end()