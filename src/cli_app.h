#ifndef __CLI_APP_H__
#define __CLI_APP_H__

#include <map>
#include <string>

#include "cli.h"

class CliApp
{
    public:
        CliApp(int argc,char* args[]);
        ~CliApp();

        void Run(std::string read_line);
};

#endif