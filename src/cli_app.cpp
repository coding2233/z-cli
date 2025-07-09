#include "cli_app.h"
#include "excel/excel_cli.h"
#include <string>
#include <vector>

CliApp::CliApp()
{
    AddClis();

    // // 执行命令
    // if(argc > 1)
    // {
    //     std::string cli_name(args[1]);
    //     if("excel" == cli_name)
    //     {
    //         ExcelCli excel_cli;
    //         excel_cli.Run(argc,args);
    //     }
    // }
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
}