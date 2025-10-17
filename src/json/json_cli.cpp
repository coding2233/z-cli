#include <iostream>
#include <filesystem>
#include <fstream>

#include "json_cli.h"
#include "spdlog/spdlog.h"
#include "core/json/json.hpp"

void JsonCli::SetupOptions()
{
    options_.add_options()
        ("h,help", "Print help")
        ("f,file", "Json file path", cxxopts::value<std::string>());

    options_.parse_positional({"file"});
}

bool JsonCli::Run(cxxopts::ParseResult result)
{
    if (result.count("help"))
    {
        std::cout << options_.help() << std::endl;
        return true;
    }

    if (result.count("file"))
    {
        auto json_file = result["file"].as<std::string>();
        std::filesystem::path json_file_path = std::filesystem::canonical(json_file);
        auto is_exists = std::filesystem::exists(json_file_path);
        if (is_exists)
        {
            try
            {
                std::string json_content;
                std::ifstream json_file_stream(json_file_path);
                std::stringstream json_stream;
                json_stream << json_file_stream.rdbuf();
                json_content = json_stream.str();
                nlohmann::json json = nlohmann::json::parse(json_content);
                SPDLOG_INFO("Json: \n{}", json.dump(4));
            }
            catch(const std::exception& e)
            {
                SPDLOG_ERROR(e.what());
            }
        }
        else
        {
            SPDLOG_WARN("Json file not exists.");
            return false;
        }
        return true;
    }
    
    SPDLOG_WARN("No json file.");
    return false;
}


