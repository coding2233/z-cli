add_requires("spdlog")
add_requires("libcurl")

target("z-core")
    set_kind("static")
    add_files("*.cpp")
    add_headerfiles("*.h")
    add_packages("spdlog")
    add_packages("libcurl")