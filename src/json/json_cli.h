
#ifndef __JSON_CLI_H__
#define __JSON_CLI_H__

#include "../cli.h"

class JsonCli:public Cli
{
    public:
        bool Run(std::vector<std::string> args) override;
        std::string GetHelp() override;

    private:
};

#endif