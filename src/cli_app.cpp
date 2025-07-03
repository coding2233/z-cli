#include "cli_app.h"
#include "excel/excel_cli.h"

CliApp::CliApp(int argc,char * args[])
{
    if(argc > 1)
    {
        std::string cli_name(args[1]);
        if("excel" == cli_name)
        {
            ExcelCli excel_cli;
            excel_cli.Run(argc,args);
        }
    }
}

CliApp::~CliApp(){}


void CliApp::Run(std::string read_line)
{
    std::cout<< "CliApp::Run "<< read_line <<std::endl;
}