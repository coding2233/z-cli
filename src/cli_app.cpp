#include "cli_app.h"
#include "core/cli_core.h"
#include "excel/excel_cli.h"
#include "spdlog/spdlog.h"
#include "update/update_cli.h"
#include <string>
#include <vector>

CliApp::CliApp(std::string app_path)
{
    // 获取当前程序的完整路径  
    std::filesystem::path executable_path = std::filesystem::canonical(app_path);  
    // 获取程序所在的目录  
    std::string app_directory = executable_path.parent_path().string();  
    SPDLOG_INFO("app_path: {}",app_path);
    SPDLOG_INFO("app_directory: {}",app_directory);
    // 创建本地文件系统，指向程序所在目录  
    auto app_fs = std::make_unique<NativeFileSystem>(app_directory);  
    app_fs->Initialize();  
    //挂载App路径
    auto vfs =  CliCore::GetCliCore().GetVirtualFileSystem();
    vfs->AddFileSystem("/app", std::move(app_fs));

    //添加更多的执行
    AddClis();
}

CliApp::~CliApp(){}


void CliApp::Run(std::string read_line)
{
    bool isActionName = true;
    std::string action;
    std::vector<std::string> args;
    char separator = ' ';
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= read_line.size(); i++)
    {
        if (read_line[i] == separator || i == read_line.size())
        {
            endIndex = i;
            std::string temp;
            temp.append(read_line, startIndex, endIndex - startIndex);
            if (isActionName) 
            {
                action = temp;
                isActionName = false;
            }
            else 
            {
                args.push_back(temp);
            }
            
            startIndex = endIndex + 1;
        }
    }
    //执行
    SPDLOG_INFO("CliApp::Run action:{}",action);
    Run(action, args);
}

 void CliApp::Run(std::string action,std::vector<std::string> args)
 {
    auto cliIter = clis_.find(action);
    if (cliIter != clis_.end()) 
    {
        cliIter->second->Run(args);
    }
 }

void CliApp::AddClis()
{
    AddCli<ExcelCli>("excel");
    AddCli<UpdateCli>("update");
}