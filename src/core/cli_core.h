#ifndef __CLI_CORE_H__
#define __CLI_CORE_H__

#include <memory>
#include <string>
#include <iostream>

#define FMT_UNICODE 0
#define VFSPP_ENABLE_MULTITHREADING

//取消系统的宏，避免与vfs冲突
#ifdef min  
#undef min  
#endif  
#ifdef max    
#undef max  
#endif


#include "spdlog/spdlog.h"
#include "vfspp/VFS.h"

using namespace vfspp;
using namespace spdlog;

class CliCore
{
private:
    VirtualFileSystemPtr vfs_;
    std::string GetUserDirectory();
public:
    static CliCore GetCliCore();
    // Function to download a file using libcurl
    int DownloadFile(const std::string& url, const std::string& outputPath);

    VirtualFileSystemPtr GetVirtualFileSystem();
    bool VFSCopyFile(std::string &src,std::string dest);
};

#endif