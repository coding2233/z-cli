
#ifndef __FANYI_CLI_H__
#define __FANYI_CLI_H__

#include "../cli.h"

class FanyiCli:public Cli
{
    public:
        bool Run(std::vector<std::string> args) override;
        std::string GetHelp() override;

    private:
        void FanyiPrint(std::string name,std::string output);
};

#endif