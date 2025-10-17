#include "excel_cli.h"

void ExcelCli::SetupOptions()
{
    options_.add_options()
        ("h,help", "Print help")
        ("f,file", "Excel file path", cxxopts::value<std::string>());
}

bool ExcelCli::Run(cxxopts::ParseResult result)
{
    if (result.count("help"))
    {
        std::cout << options_.help() << std::endl;
        return true;
    }

    if (result.count("file"))
    {
        std::string file = result["file"].as<std::string>();
        std::cout << "Processing excel file: " << file << std::endl;
    }
    else
    {
        std::cout << options_.help() << std::endl;
    }

    return true;
}

