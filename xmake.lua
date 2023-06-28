--config
local libXoXdir = "/home/dream/Program/XoX/target/"
local compiler = "clang"








add_languages("c++20")
add_toolchains(compiler)
--add_rules("mode.debug","mode.release")
local libName = "XoX"
target(libName)
set_kind("shared")
set_targetdir(libXoXdir)
add_files("./XoX/src/**.ixx")
target_end()

target("SandBox")
set_kind("binary")
set_targetdir("./target/")
add_files("./XoX/src/**.ixx")
add_files("./SandBox/src/**.cc")
add_linkdirs(libXoXdir)
add_links(libName)
target_end()

