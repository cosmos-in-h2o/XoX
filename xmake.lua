-- 添加模式
add_rules("mode.debug","mode.release")

-- c++23
set_languages("c++23")

-- 引擎主体
target("XoX")
    --动态库类型
    set_kind("shared")
	--如果是Windows就导出所有函数与类到动态库中
	if is_plat("windows") then
		add_rules("utils.symbols.export_all", {export_classes = true})
	end
    -- 头文件包含
    add_includedirs("./include/")
    add_includedirs("./thirdparty/include/")
    -- 导出dll宏
    add_defines("XOX_EXPORT")
    -- 模块接口文件与源文件
    add_files("./core/**.cxx",{public=true})
	add_files("./world/**.cxx",{public=true})
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
    add_files("./editor/src/**.ixx")
    add_files("./editor/src/**.cc")
    -- 引擎依赖
    add_deps("XoX")
    -- 导出目录
    set_targetdir("./bin/")
target_end()
