#ifndef __CLI_H__
#define __CLI_H__

#include <string>
#include <iostream>
#include <vector>

class Cli
{
    public:
        virtual bool Run(std::vector<std::string> args) = 0;
        virtual std::string GetHelp() = 0;
};

#endif