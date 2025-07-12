#include "update_cli.h"
#include "spdlog/spdlog.h"
#include <algorithm>



bool UpdateCli::Run(std::vector<std::string> args) 
{
    SPDLOG_INFO("UpdateCli::Run");

    // std::string url = "http://speedtest.tele2.net/1MB.zip";
    std::string url = "https://github.com/coding2233/z-cli/releases/download/nightly/";
    std::string file_name;
#if _WIN32
    file_name = "z-cli-windows-x64.zip";
#elif __APPLE__
    file_name = "z-cli-macosx-arm64.zip";
#elif __linux__
    file_name = "z-cli-linux-x86_64.zip";
#endif
    url.append(file_name);
    SPDLOG_INFO("Download url:{}",url,file_name);
    int ret = CliCore::GetCliCore().DownloadFile(url,file_name);
    SPDLOG_INFO("Download result:{} file_name:{}",ret,file_name);
    
    if (ret == 0) 
    {
        
        IFileSystemPtr update_fs = std::make_unique<ZipFileSystem>(file_name);
        update_fs->Initialize();
        auto file_list = update_fs->FileList();

       
        //挂载下载的文件到/update下
        CliCore::GetCliCore().GetVirtualFileSystem()->AddFileSystem("/update",std::move(update_fs));

        //复制/update -> /app下进行更新
        for(auto iter = file_list.begin();iter!= file_list.end();iter++)
        {
            SPDLOG_INFO("{}",iter->first);

            std::string src = "/update/" + iter->first;
            std::string dest = "/app/"+iter->first;
            CliCore::GetCliCore().CopyFile(src, dest);
        }
    }

    return false;
}
