-- 编译的时候生成 compile_commands
add_rules("plugin.compile_commands.autoupdate")

add_rules("mode.debug", "mode.release")
-- 添加下面这行来强制为所有 target 开启调试符号
if is_mode("debug") then
    set_symbols("debug")
end

add_repositories("my-repo my-repositories")
add_requires("xlnt",{configs = {shared = false}})
-- add_requires("llama.cpp",{configs = {vulkan = true}})
add_requires("llama.cpp")

set_languages("cxx17","c17")

includes("src/*")

target("z-cli")
    add_files("src/*.cpp","src/update/*.cpp")
    add_deps("z-core")
    add_deps("excel-cli","fanyi-cli","json-cli")