
#ifndef __LLAMA_CLI_H__
#define __LLAMA_CLI_H__

#include "../cli.h"

class LlamaCli:public Cli
{
    public:
        bool Run(std::vector<std::string> args) override;
        std::string GetHelp() override;

    private:
        int RunModel(std::string model_path, std::string prompt);
};

#endif