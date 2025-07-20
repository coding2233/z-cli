#ifndef __CLI_CORE_H__
#define __CLI_CORE_H__

#include <memory>
#include <string>
#include <iostream>
#include <type_traits>
#include <curl/curl.h>

#if _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define FMT_UNICODE 0
#define VFSPP_ENABLE_MULTITHREADING

//取消系统的宏，避免与vfs冲突
#ifdef min  
#undef min  
#endif  
#ifdef max    
#undef max  
#endif

#define UTF_CPP_CPLUSPLUS 201103L

#include "spdlog/spdlog.h"
#include "vfspp/VFS.h"
#include "json.hpp"

using namespace vfspp;
using namespace spdlog;

class CliCore
{
private:
    VirtualFileSystemPtr vfs_;
    std::string app_path_;
public:
    static CliCore& GetCliCore();
    // Function to download a file using libcurl
    int DownloadFile(const std::string& url, const std::string& outputPath);

    int Get(std::string &url,std::string &response);

    std::string GetUserDirectory();
    void SetAppPath(std::string path);
    std::string GetAppPath();

    VirtualFileSystemPtr GetVirtualFileSystem();
    bool VFSCopyFile(std::string &src,std::string dest);

    void AddNativeFileSystem(std::string &alias, std::string &path);

    bool VaildUTF8String(std::string &tetx);

    void WaitSleep(int second);
};

#endif