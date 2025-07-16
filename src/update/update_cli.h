#ifndef __CLI_UPDATE_H__
#define __CLI_UPDATE_H__ 

#include "../cli.h"
#include "../core/cli_core.h"

class UpdateCli:public Cli
{ 
    public: 
        std::string GetHelp() override
        {
            return "update";
        }
        bool Run(std::vector<std::string> args) override;
    private:
        void Download();
        void Update(std::string zip_file,std::string bin_path);
};

#endif