add_requires("libcurl")

target("z-core")
    set_kind("static")
    add_files("*.cpp")
    add_packages("libcurl")