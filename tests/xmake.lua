target("tests")
    set_kind("binary")
    set_languages("cxx17")
    
    add_includedirs("..", "../src", "../src/core")
    add_files("test_main.cpp")
    
    add_deps("z-core")
    add_packages("cxxopts")
    
    -- 添加测试目标到主构建
    add_tests("default")