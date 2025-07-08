#ifndef __CLI_H__
#define __CLI_H__

#include <string>
#include <iostream>

class Cli
{
    public:
        virtual bool Run(std::string line) = 0;
        virtual std::string GetHelp() = 0;
};

#endif