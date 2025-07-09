#ifndef __EXCEL_CLI_H__
#define __EXCEL_CLI_H__

#include "../cli.h"

class ExcelCli:public Cli
{
    public:
        bool Run(std::vector<std::string> args) override;
        std::string GetHelp() override;
};

#endif