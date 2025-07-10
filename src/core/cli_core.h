#ifndef __CLI_CORE_H__
#define __CLI_CORE_H__

#include <memory>
#include <string>
#include <iostream>

#define FMT_UNICODE 0

#include "spdlog/spdlog.h"

class CliCore
{
private:
public:
    static CliCore GetCliCore();
    // Function to download a file using libcurl
    bool DownloadFile(const std::string& url, const std::string& outputPath);
};

#endif