
#ifndef __FANYI_CLI_H__
#define __FANYI_CLI_H__

#include "cli.h"

class FanyiCli : public Cli
{
    public:
        FanyiCli(std::string name) : Cli(name, "Translate text") {}
        void SetupOptions() override;
        bool Run(cxxopts::ParseResult result) override;
    private:
        void FanyiPrint(std::string name,std::string output);
};

#endif