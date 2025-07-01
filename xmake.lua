includes("src/*")

target("z-cli")
    add_files("src/*.cpp")
    add_deps("excel_cli")