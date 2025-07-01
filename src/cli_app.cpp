#include "cli_app.h"
#include "excel/excel_cli.h"

CliApp::CliApp(int argc,char * args[])
{
    std::string cli_name(args[1]);

    if("excel" == cli_name)
    {
        ExcelCli excel_cli;
        excel_cli.Run(argc,args);
    }
}

CliApp::~CliApp(){}