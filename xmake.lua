includes("src/*")

target("z-cli")
    add_files("src/*.cpp")
    add_deps("z-core","excel_cli")