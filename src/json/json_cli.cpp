#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

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
        
        try
        {
            // 检查文件是否存在
            if (!std::filesystem::exists(json_file))
            {
                std::cerr << "Error: File '" << json_file << "' does not exist." << std::endl;
                return false;
            }
            
            // 获取规范路径
            std::filesystem::path json_file_path = std::filesystem::canonical(json_file);
            
            // 检查是否为常规文件
            if (!std::filesystem::is_regular_file(json_file_path))
            {
                std::cerr << "Error: '" << json_file << "' is not a regular file." << std::endl;
                return false;
            }
            
            // 读取文件内容
            std::ifstream json_file_stream(json_file_path);
            if (!json_file_stream.is_open())
            {
                std::cerr << "Error: Cannot open file '" << json_file << "' for reading." << std::endl;
                return false;
            }
            
            std::stringstream json_stream;
            json_stream << json_file_stream.rdbuf();
            std::string json_content = json_stream.str();
            
            if (json_content.empty())
            {
                std::cerr << "Error: File '" << json_file << "' is empty." << std::endl;
                return false;
            }
            
            // 解析JSON
            try
            {
                nlohmann::json json = nlohmann::json::parse(json_content);
                std::cout << "JSON content from '" << json_file << "':" << std::endl;
                std::cout << json.dump(4) << std::endl;
                SPDLOG_INFO("Successfully parsed JSON file: {}", json_file);
                return true;
            }
            catch (const nlohmann::json::parse_error& e)
            {
                std::cerr << "Error: Invalid JSON in file '" << json_file << "': " << e.what() << std::endl;
                SPDLOG_ERROR("JSON parse error in {}: {}", json_file, e.what());
                return false;
            }
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << "Error: File system error with '" << json_file << "': " << e.what() << std::endl;
            SPDLOG_ERROR("File system error: {}", e.what());
            return false;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: Unexpected error processing '" << json_file << "': " << e.what() << std::endl;
            SPDLOG_ERROR("Unexpected error: {}", e.what());
            return false;
        }
    }
    
    std::cerr << "Error: No JSON file specified. Use --help for usage information." << std::endl;
    return false;
}


