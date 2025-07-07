#ifndef __CLI_H__
#define __CLI_H__

#include <string>
#include <iostream>

class Cli
{
    public:
        virtual void Run(int argc,char* args[]) = 0;
        virtual std::string GetName() = 0;
        virtual std::string GetHelp() = 0;
};

#endif