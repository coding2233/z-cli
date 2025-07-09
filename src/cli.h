#ifndef __CLI_H__
#define __CLI_H__

#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "core/cli_core.h"

class Cli
{
    public:
        virtual bool Run(std::vector<std::string> args) = 0;
        virtual std::string GetHelp() = 0;
        std::unique_ptr<CliCore> GetCliCore();
};

#endif