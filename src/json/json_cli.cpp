#include <iostream>
#include <filesystem>

#include "json_cli.h"
#include "spdlog/spdlog.h"



  std::string JsonCli::GetHelp()
  {
    return "JsonCli";
  }

bool JsonCli::Run(std::vector<std::string> args)
{
    if (args.size() > 0) 
    {
        auto json_file = args[0];
         // 获取当前程序的完整路径  
        std::filesystem::path json_file_path = std::filesystem::canonical(json_file);  
        auto is_exists = std::filesystem::exists(json_file_path);
        if (is_exists)
        {
            //获取文件内容，解析json, 如果解析失败，打印错误信息
            try
            {
                std::string json_content;
                std::ifstream json_file(json_file_path);
                std::stringstream json_stream;
                json_stream << json_file.rdbuf();
                json_content = json_stream.str();
                nlohmann::json json = nlohmann::json::parse(json_content);
                SPDLOG_INFO("Json: \n{}",json.dump(4));
            }
            catch(const std::exception& e)
            {
                SPDLOG_ERROR( e.what());
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


