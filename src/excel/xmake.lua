includes("../core")

target("excel-cli")
    set_kind("static")
    add_files("*.cpp")
    add_deps("z-core")
    add_packages("xlnt")