#include "update_cli.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <cstdlib>
#include <future>


bool UpdateCli::Run(std::vector<std::string> args) 
{
    SPDLOG_INFO("UpdateCli::Run");

    if (args.size() ==2) 
    {
        Update(args[0],args[1]);
    }
    else 
    {
        Download();
    }
    return true;
}


void UpdateCli::Download()
{
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

        //复制z-cli
        //复制/update -> /app下进行更新
        std::string updater_name;
        for(auto iter = file_list.begin();iter!= file_list.end();iter++)
        {
            if (iter->first.find("/z-cli") != std::string::npos) 
            {
                SPDLOG_INFO("{}",iter->first);

                std::string src = "/update" + iter->first;
                updater_name = "z-cli-updater"+iter->first.substr(6);
                CliCore::GetCliCore().VFSCopyFile(src, "/"+updater_name);
            }
        }

        //运行程序
        std::string updater_basepath = CliCore::GetCliCore().GetUserDirectory();
        std::string app_basepath = CliCore::GetCliCore().GetAppPath();
        std::string updater_path = updater_basepath.append("/").append(updater_name);
         std::string spile_char = "/";
        #if _WIN32
        spile_char = "\\";
        #endif
        std::string cmd = updater_basepath.append(spile_char).append(updater_name).append(" ").append(app_basepath).append(spile_char).append(file_name).append(" ").append(app_basepath);
        SPDLOG_INFO("cmd: {}",cmd);
       std::async(std::launch::async, [cmd]() {
            std::system(cmd.c_str());
        });
        exit(0);
    }
}

void UpdateCli::Update(std::string zip_file,std::string bin_path)
{
    IFileSystemPtr update_fs = std::make_unique<ZipFileSystem>(zip_file);
    update_fs->Initialize();
    auto file_list = update_fs->FileList();
    //挂载下载的文件到/update下
    CliCore::GetCliCore().GetVirtualFileSystem()->AddFileSystem("/update",std::move(update_fs));

    //挂在/update-app
    std::string update_app_name = std::string("/update-app");
    CliCore::GetCliCore().AddNativeFileSystem(update_app_name,bin_path);

    //复制/update -> /app下进行更新
    for(auto iter = file_list.begin();iter!= file_list.end();iter++)
    {
        SPDLOG_INFO("{}",iter->first);

        std::string src = "/update" + iter->first;
        std::string dest = "/update-app"+iter->first;
        CliCore::GetCliCore().VFSCopyFile(src, dest);
    }
    SPDLOG_INFO("Update Success.");
    exit(0);
}