#include "cli_update.h"

bool CliUpdate::Run(std::vector<std::string> args) 
{
    // std::string url = "http://speedtest.tele2.net/1MB.zip";
    std::string url = "https://github.com/coding2233/z-cli/releases/download/nightly/";
    std::string file_name;
#if _WIN32
    file_name = "z-cli-windows-x86_64.zip";
#elif __APPLE__
    file_name = "z-cli-macosx-arm64.zip";
#elif __linux__
    file_name = "z-cli-linux-x86_64.zip";
#endif
    url.append(file_name);

    CliCore::GetCliCore().DownloadFile(url,file_name);

    return false;
}
