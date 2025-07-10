includes("src/*")

target("z-cli")
    add_files("src/*.cpp","src/update/*.cpp")
    add_deps("z-core")
    add_deps("excel_cli")