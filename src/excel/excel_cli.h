#ifndef __EXCEL_CLI_H__
#define __EXCEL_CLI_H__

#include "cli.h"

class ExcelCli : public Cli
{
    public:
        ExcelCli(std::string name) : Cli(name, "Excel file operations") {}
        void SetupOptions() override;
        bool Run(cxxopts::ParseResult result) override;
};

#endif