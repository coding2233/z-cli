
add_requires("libcurl")

target("z-core")
    set_kind("static")
    add_includedirs("spdlog-1.15.3/include",{public=true})
    add_includedirs("vfspp/include",{public=true})
    add_includedirs("vfspp/include/vfspp",{public=true})
    add_includedirs("vfspp/vendor/miniz-cpp",{public=true})
    add_includedirs("utf8cpp",{public=true})
    add_files("*.cpp")
    add_packages("libcurl",{public = true })