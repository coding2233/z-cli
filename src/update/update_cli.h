#ifndef __CLI_UPDATE_H__
#define __CLI_UPDATE_H__ 

#include "../cli.h"
#include "../core/cli_core.h"

class UpdateCli:public Cli
{
    public:
        UpdateCli(std::string name) : Cli(name, "Update the z-cli application") {}
        std::string GetHelp()
        {
            return "update";
        }        void SetupOptions() override;
        bool Run(cxxopts::ParseResult result) override;
    private:
        void Download();
        void Update(std::string zip_file,std::string bin_path);
};

#endif