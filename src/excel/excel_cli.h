#ifndef __EXCEL_CLI_H__
#define __EXCEL_CLI_H__

#include "../cli.h"

class ExcelCli:public Cli
{
    public:
        void Run(int argc,char* args[]) override;
};

#endif