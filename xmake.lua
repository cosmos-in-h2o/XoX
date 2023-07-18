-- 添加模式
add_rules("mode.debug","mode.release")
-- c++23
set_languages("c++23")
-- 引擎主体
target("XoX")
    --动态库类型
    set_kind("shared")
    -- 头文件包含
    add_includedirs("./include/")
    -- 导出dll宏
    add_defines("XOX_EXPORT")
    -- 模块接口文件与源文件
    add_files("./core/**.ixx")
    add_files("./core/**.cc")
    set_targetdir("./target/")
target_end()