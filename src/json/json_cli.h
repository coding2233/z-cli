
#ifndef __JSON_CLI_H__
#define __JSON_CLI_H__

#include "cli.h"

class JsonCli : public Cli
{
    public:
        JsonCli(std::string name) : Cli(name, "JSON operations") {}
        void SetupOptions() override;
        bool Run(cxxopts::ParseResult result) override;
};

#endif