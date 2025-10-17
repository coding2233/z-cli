includes("../core")

target("fanyi-cli")
    set_kind("static")
    add_files("*.cpp")
    add_includedirs("$(projectdir)/src")
    add_deps("z-core")