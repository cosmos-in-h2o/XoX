target("interface")
	set_kind("static")
	add_files("interface/src/*.cc")
	set_targetdir("../bin")
	add_includedirs("interface/include",{public=true})
target_end()

target("mpack")
	set_kind("binary")
	add_files("mpack/src/*.cc")
	set_targetdir("../bin")
	add_includedirs("mpack/include",{public=true})
target_end()

target("xox")
	set_kind("binary")
	add_files("xox-cmd/src/*.cc")
	set_targetdir("../bin")
	add_includedirs("xox-cmd/include")
	add_deps("interface")
	add_deps("mpack")
target_end()



