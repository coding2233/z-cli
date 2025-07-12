#ifndef __CLI_CORE_H__
#define __CLI_CORE_H__

#include <memory>
#include <string>
#include <iostream>

#define FMT_UNICODE 0

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
    bool CopyFile(std::string &src,std::string dest);
};

#endif