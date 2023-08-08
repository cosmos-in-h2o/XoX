add_rules("mode.debug","mode.release")
-- c++23
set_languages("c++23")
add_subdirs("thirdparty")
-- 引擎主体
target("XoX")
    --动态库类型
    set_kind("shared")
    -- 头文件包含
	add_includedirs("./")
    add_includedirs("include")
    add_includedirs("thirdparty/include")
    -- 导出dll宏
    add_defines("XOX_EXPORT")
    -- 模块接口文件与源文件
    -- add_files("./core/**.ixx",{public=true})
	-- add_files("./world/**.ixx",{public=true})
    add_files("core/**.cc")
    add_files("world/**.cc")
    -- 项目依赖
	if is_plat("windows") then
		add_links("Advapi32")
	end
    add_linkdirs("lib")
	add_links("mimalloc")
	
    -- 导出目录
    set_targetdir("./bin/")
target_end()
