add_repositories("my-repo my-repositories")
add_requires("xlnt",{configs = {shared = false}})
-- add_requires("llama.cpp",{configs = {vulkan = true}})
add_requires("llama.cpp")

set_languages("cxx17","c17")

includes("src/*")

target("z-cli")
    add_files("src/*.cpp","src/update/*.cpp")
    add_deps("z-core")
    add_deps("excel-cli","fanyi-cli","llama-cli")