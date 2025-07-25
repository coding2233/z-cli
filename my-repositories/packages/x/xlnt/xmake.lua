package("xlnt")

    set_homepage("https://github.com/tfussell/xlnt")
    set_description("Cross-platform user-friendly xlsx library for C++11+")
    set_license("MIT")

    -- add_urls("https://github.com/tfussell/xlnt.git")
    add_urls("https://gitee.com/mirrors/xlnt.git")
    

    add_versions("2023.03.02", "297b331435d6dee09bf89c8a5ad974b01f18039b")
    --add_versions("2024.10.10", "297b331435d6dee09bf89c8a5ad974b01f18039b")

    -- 版本号 patch文件路径 sha256(sha256sum)
    --add_patches("2024.10.10",path.join(os.scriptdir(), "patches", "2023.03.02", "xlnt_config.hpp.patch"),"c6bcc9eacdedeaf0b4002266dc85beee8ef6b01820add897f133e75468e1bbdd")
    add_patches("2023.03.02",path.join(os.scriptdir(), "patches", "2023.03.02", "xlnt_config.hpp.patch"),"c6bcc9eacdedeaf0b4002266dc85beee8ef6b01820add897f133e75468e1bbdd")

    add_configs("python", {description = "Build Arrow conversion functions", default = true, type = "boolean", readonly = true})

    add_deps("cmake")
    add_links("xlnt")

    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        table.insert(configs, "-DSTATIC=" .. (package:config("shared") and "OFF" or "ON"))
        import("package.tools.cmake").install(package, configs)
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            #include <xlnt/xlnt.hpp>

            void test(){
                xlnt::workbook wb;
                xlnt::worksheet ws = wb.active_sheet();
                ws.cell("A1").value(5);
                wb.save("example.xlsx");
            }
        ]]}, {configs = {languages = "c++14"}}))
    end)