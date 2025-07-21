#ifndef __CLI_APP_H__
#define __CLI_APP_H__

#include <map>
#include <memory>
#include <string>
#include <vector>


#include "cli.h"

#define CLI_APP_VERSION "1.0.0"

class CliApp
{
    public:
        CliApp();
        ~CliApp();

        int Run(int argc,char* args[]);

        void Run(std::string read_line);
        void Run(std::string action,std::vector<std::string> agrs);

    private:
        std::map<std::string,std::shared_ptr<Cli>> clis_;  

        void Init(std::string app_path);

        template<class T>
        void AddCli(std::string name)
        {
            clis_.insert(std::make_pair(name,std::make_shared<T>()));
        }

        void AddClis();

};

#endif