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

includes("src/core", "src/excel", "src/fanyi", "src/json", "src/update")

add_plugindirs("xmake/plugins")

target("gen_add_clis_file")
    set_kind("phony")
    on_build(function(target)
        import("core.project.task")
        task.run("gen_add_clis")
    end)

target("z-cli")
    add_deps("gen_add_clis_file")
    add_files("src/*.cpp")
    add_files("src/generated/add_clis.cpp")
    add_includedirs("src")
    add_deps("z-core", "excel-cli", "fanyi-cli", "json-cli", "update-cli")
