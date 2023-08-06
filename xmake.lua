add_rules("mode.debug","mode.release")
-- c++23
set_languages("c++23")
add_subdirs("thirdparty")
-- 引擎主体
target("XoX")
    --动态库类型
    set_kind("shared")
    -- 头文件包含
    add_includedirs("./include/")
    add_includedirs("./thirdparty/include/")
    -- 导出dll宏
    add_defines("XOX_EXPORT")
    -- 模块接口文件与源文件
    add_files("./core/**.cppm",{public=true})
	add_files("./world/**.cppm",{public=true})
    add_files("./core/**.cc")
    add_files("./world/**.cc")
    -- 项目依赖
    add_linkdirs("./thirdparty/lib/")
    -- 导出目录
    set_targetdir("./bin/")
target_end()

-- 编辑器
target("XoX-editor")
    -- 可执行文件
    set_kind("binary")
    -- 头文件包含
    add_includedirs("./include/")
    add_includedirs("./thirdparty/include/")
    -- 自身源文件
    add_files("./editor/src/**.cppm")
    add_files("./editor/src/**.cc")
    -- 依赖
	add_linkdirs("./bin")
    add_deps("XoX")
    -- 导出目录
    set_targetdir("./bin/")
target_end()
