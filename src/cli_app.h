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

    int Run(int argc, char* args[]);

private:
    std::map<std::string, std::shared_ptr<Cli>> clis_;

    void Initialize(std::string app_path);
    std::string GetAppPath(std::string app_path);
    void SetupVirtualFileSystem(const std::string& app_directory);
    void LoadConfiguration();
    void InitializeLogging();

    template<class T>
    void AddCli(std::string name)
    {
        clis_.insert(std::make_pair(name, std::make_shared<T>(name)));
    }

    void AddClis();
};

#endif // __CLI_APP_H__