#include <cstdlib>
#include <string>
#include <vector>

#include "cli_app.h"
#include "core/cli_core.h"
#include "excel/excel_cli.h"
#include "fanyi/fanyi_cli.h"
#include "spdlog/spdlog.h"
#include "update/update_cli.h"


#include "utf8_console.h"

CliApp::CliApp()
{
   
}

CliApp::~CliApp(){}


int CliApp::Run(int argc,char* args[])
{
    //控制台支持utf-8
    initialize_utf8_console();
    //初始化
    Init(args[0]);
    //参数
    std::string action;
    std::vector<std::string> action_args;
    if(argc < 2)
    {
        std::string read_line;
        while(true)
        {
            std::cout<<"z-cli> ";
            read_line.clear();
            // std::cin.clear();
            // rewind(stdin);
            std::getline(std::cin,read_line);
            Run(read_line);
        }
    }
    else 
    {
        action = args[1];
        for(int i = 2;i < argc;i++)
        {
            action_args.push_back(args[i]);
        }
        Run(action,action_args);
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
    
    Run(action, args);
}

 void CliApp::Run(std::string action,std::vector<std::string> args)
 {
    if ("exit" == action) {
        exit(0);
    }

    auto cliIter = clis_.find(action);
    if (cliIter != clis_.end()) 
    {
        SPDLOG_INFO("CliApp::Run action:{}",action);
        cliIter->second->Run(args);
    }
    else {
        SPDLOG_WARN("CliApp::Run not found action:{}",action);
    }
 }

void CliApp::AddClis()
{
    AddCli<ExcelCli>("excel");
    AddCli<UpdateCli>("update");
    AddCli<FanyiCli>("fy");
}

std::string CliApp::GetAppPath(std::string app_path)
{
    #ifdef _WIN32
    if (app_path.find("\\")==std::string::npos)
    {
        std::string env_path = std::string(getenv("PATH"));
        // SPDLOG_INFO("env_path: {}",env_path);
        int start_index= 0 ;
        int find_index = 0;
        for (size_t i = 0; i < env_path.size(); i++)
        {
            if (';'== env_path[i])
            {
                find_index = i;
                SPDLOG_INFO("start_index:{} find_index:{} length:{} env_size:{}",start_index,find_index,find_index-start_index,env_path.size());
                std::string find_app_path = env_path.substr(start_index,find_index-start_index)+"\\"+app_path+".exe";
                SPDLOG_INFO("find_app_path: {}",find_app_path);
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
        std::string env_path = std::string(getenv("PATH"));
        // SPDLOG_INFO("env_path: {}",env_path);
        int start_index= 0 ;
        int find_index = 0;
        for (size_t i = 0; i < env_path.size(); i++)
        {
            if (':'== env_path[i])
            {
                find_index = i;
                SPDLOG_INFO("start_index:{} find_index:{} length:{} env_size:{}",start_index,find_index,find_index-start_index,env_path.size());
                std::string find_app_path = env_path.substr(start_index,find_index-start_index)+"/"+app_path;
                SPDLOG_INFO("find_app_path: {}",find_app_path);
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
