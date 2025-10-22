#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "cli_app.h"
#include "core/cli_core.h"
#include "excel/excel_cli.h"
#include "fanyi/fanyi_cli.h"
#include "spdlog/spdlog.h"
#include "update/update_cli.h"
#include "json/json_cli.h"


#include "utf8_console.h"

CliApp::CliApp()
{
   
}

CliApp::~CliApp(){}


#include "cxxopts.hpp"

int CliApp::Run(int argc,char* args[])
{
    //控制台支持utf-8
    initialize_utf8_console();
    
    
    //初始化
    Init(args[0]);

    cxxopts::Options options("z-cli", "A command line tool for z.");
    options.add_options()
        ("h,help", "Print help")
        ("command", "The command to execute", cxxopts::value<std::string>())
        ("args", "Arguments for the command", cxxopts::value<std::vector<std::string>>());

    options.parse_positional({"command", "args"});
    options.allow_unrecognised_options();

    auto result = options.parse(argc, args);

    // 检查是否是子命令的help请求
    bool has_command = result.count("command");
    bool has_help = result.count("help");
    
    if (has_help && !has_command)
    {
        std::cout << options.help() << std::endl;
        std::cout << "\nAvailable commands:\n";
        for (const auto& pair : clis_)
        {
            std::cout << "  " << pair.first << " - " << pair.second->GetHelpText() << "\n";
        }
        std::cout << "\nUse 'z-cli <command> --help' for more information about a command.\n";
        return 0;
    }

    if (result.count("command"))
    {
        std::string command = result["command"].as<std::string>();
        auto it = clis_.find(command);
        if (it != clis_.end())
        {
            auto& cli = it->second;
            cli->SetupOptions();
            auto& cli_options = cli->GetOptions();
            
            // 检查是否有--help参数
            bool has_help = false;
            for (int i = 1; i < argc; ++i) {
                if (std::string(args[i]) == "--help" || std::string(args[i]) == "-h") {
                    has_help = true;
                    break;
                }
            }
            
            if (has_help) {
                std::cout << cli_options.help() << std::endl;
                return 0;
            }
            
            // 收集命令后的参数
            std::vector<std::string> cli_args;
            bool found_command = false;
            for (int i = 1; i < argc; ++i) {
                if (std::string(args[i]) == command) {
                    found_command = true;
                } else if (found_command) {
                    cli_args.push_back(std::string(args[i]));
                }
            }
            
            // 构建新的argv
            std::vector<char*> new_argv;
            new_argv.push_back(const_cast<char*>(args[0])); // 程序名
            for (auto& arg : cli_args) {
                new_argv.push_back(const_cast<char*>(arg.c_str()));
            }
            
            auto cli_result = cli_options.parse(new_argv.size(), new_argv.data());
            return cli->Run(cli_result);
        }
        else
        {
            std::cout << "Unknown command: " << command << std::endl;
            return 1;
        }
    }
    else
    {
        // Interactive mode
        std::cout << "z-cli interactive mode. Type 'help' for commands or 'exit' to quit." << std::endl;
        std::string read_line;
        while (true)
        {
            std::cout << "z-cli> ";
            std::getline(std::cin, read_line);
            
            // Handle Windows CRLF line endings
            if (!read_line.empty() && read_line.back() == '\r') {
                read_line.pop_back();
            }
            
            // Trim whitespace
            read_line.erase(0, read_line.find_first_not_of(" \t\n\r"));
            read_line.erase(read_line.find_last_not_of(" \t\n\r") + 1);
            
            if (read_line.empty() || read_line == "exit" || read_line == "quit")
            {
                break;
            }
            
            if (read_line == "help")
            {
                std::cout << "Available commands:\n";
                for (const auto& pair : clis_)
                {
                    std::cout << "  " << pair.first << " - " << pair.second->GetHelpText() << "\n";
                }
                std::cout << "  help - Show this help message\n";
                std::cout << "  exit/quit - Exit interactive mode\n";
                continue;
            }
            
            // Parse interactive command
            std::istringstream iss(read_line);
            std::string command;
            iss >> command;
            
            auto it = clis_.find(command);
            if (it != clis_.end())
            {
                auto& cli = it->second;
                cli->SetupOptions();
                auto& cli_options = cli->GetOptions();
                
                // Collect remaining arguments
                std::vector<std::string> args;
                std::string arg;
                while (iss >> arg) {
                    args.push_back(arg);
                }
                
                // Build argv for cxxopts
                std::vector<char*> argv;
                argv.push_back(const_cast<char*>("z-cli")); // program name
                
                // Check for help flag
                bool has_help = false;
                for (const auto& a : args) {
                    if (a == "--help" || a == "-h") {
                        has_help = true;
                        break;
                    }
                    argv.push_back(const_cast<char*>(a.c_str()));
                }
                
                if (has_help) {
                    std::cout << cli_options.help() << std::endl;
                } else if (args.empty()) {
                    std::cout << cli_options.help() << std::endl;
                } else {
                    try {
                        auto result = cli_options.parse(argv.size(), argv.data());
                        cli->Run(result);
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                        std::cout << cli_options.help() << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "Unknown command: " << command << std::endl;
                std::cout << "Type 'help' for available commands." << std::endl;
            }
        }
    }

    return 0;
}


void CliApp::Init(std::string app_path)
{
    SPDLOG_INFO("Init app_path: {}",app_path);
    app_path = GetAppPath(app_path);
    SPDLOG_INFO("app_path: {}",app_path);
    // 获取当前程序的完整路径  
    std::filesystem::path executable_path = std::filesystem::canonical(app_path);  
    // 获取程序所在的目录  
    std::string app_directory = executable_path.parent_path().string();  
    SPDLOG_INFO("app_directory: {}",app_directory);
    CliCore::GetCliCore().SetAppPath(app_directory);
    // 创建本地文件系统，指向程序所在目录  
    auto app_fs = std::make_unique<NativeFileSystem>(app_directory);  
    app_fs->Initialize();  
    //挂载App路径
    auto vfs =  CliCore::GetCliCore().GetVirtualFileSystem();
    vfs->AddFileSystem("/app", std::move(app_fs));

    //添加更多的执行
    AddClis();

    //https://appworlds.cn/translate
    // std::string url = std::string("https://translate.appworlds.cn/?text=This%20is%20a%20test%20text&from=en&to=zh-CN");
    // // std::string url = std::string("https://translate.appworlds.cn?text=This is a test text&from=en&to=zh-CN");
    // std::string response;
    // int ret = CliCore::GetCliCore().Get(url,response);
    // SPDLOG_INFO("url->{} {}",ret,response);
}




// This function is now automatically generated by a script.
// See scripts/gen_add_clis.lua

std::string CliApp::GetAppPath(std::string app_path)
{
    #ifdef _WIN32
    if (app_path.find(R"(\)")==std::string::npos)
    {
        const char* env_var = std::getenv("PATH");
        if (!env_var) env_var = std::getenv("Path");  // Windows might use "Path"
        if (!env_var) return app_path;  // No PATH environment variable found
        std::string env_path = std::string(env_var);
        // SPDLOG_INFO("env_path: {}",env_path);
        int start_index= 0 ;
        int find_index = 0;
        for (size_t i = 0; i < env_path.size(); i++)
        {
            if (';'== env_path[i])
            {
                find_index = i;
                // SPDLOG_INFO("start_index:{} find_index:{} length:{} env_size:{}",start_index,find_index,find_index-start_index,env_path.size());
                std::string find_app_path = env_path.substr(start_index,find_index-start_index)+"\\"+app_path+".exe";
                // SPDLOG_INFO("find_app_path: {}",find_app_path);
                if (std::filesystem::exists(find_app_path))
                {
                    app_path = find_app_path;
                    break;
                }
                else
                {
                    start_index = find_index+1;
                }
            }
        }
    }
    #else
    if (app_path.find("/")==std::string::npos)
    {
        const char* env_var = std::getenv("PATH");
        if (!env_var) return app_path;  // No PATH environment variable found
        std::string env_path = std::string(env_var);
        // SPDLOG_INFO("env_path: {}",env_path);
        int start_index= 0 ;
        int find_index = 0;
        for (size_t i = 0; i < env_path.size(); i++)
        {
            if (':'== env_path[i])
            {
                find_index = i;
                // SPDLOG_INFO("start_index:{} find_index:{} length:{} env_size:{}",start_index,find_index,find_index-start_index,env_path.size());
                std::string find_app_path = env_path.substr(start_index,find_index-start_index)+"/"+app_path;
                // SPDLOG_INFO("find_app_path: {}",find_app_path);
                if (std::filesystem::exists(find_app_path))
                {
                    app_path = find_app_path;
                    break;
                }
                else
                {
                    start_index = find_index+1;
                }
            }
        }
    }
    #endif
    return app_path;
}
