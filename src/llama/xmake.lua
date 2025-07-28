includes("../core")

target("llama-cli")
    set_kind("static")
    add_files("*.cpp")
    add_packages("llama.cpp", {configs = {vulkan = false}})
    add_deps("z-core")