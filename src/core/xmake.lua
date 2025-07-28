
add_requires("libcurl")

target("z-core")
    set_kind("static")
    set_languages("cxx17")
    if is_plat("windows") then 
        add_cflags("/utf-8")
        add_cxflags("/utf-8")
        add_cxxflags("/utf-8")
    end 
    add_includedirs("spdlog-1.15.3/include",{public=true})
    add_includedirs("vfspp/include",{public=true})
    add_includedirs("vfspp/include/vfspp",{public=true})
    add_includedirs("vfspp/vendor/miniz-cpp",{public=true})
    -- add_includedirs("utf8cpp",{public=true})
    add_includedirs("json",{public=true})
    add_includedirs("utf8-console/include",{public=true})
    add_files("utf8-console/src/*.cpp","utf8-console/src/*.c")
    add_files("*.cpp")
    add_packages("libcurl",{public = true })
    add_packages("llama.cpp",{public = true})
    -- add_packages("llama.cpp", {configs = {vulkan = false}})