includes("../core")

target("excel_cli")
    set_kind("static")
    add_files("*.cpp")
    add_deps("z-core")