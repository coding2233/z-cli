#ifndef __CLI_CORE_H__
#define __CLI_CORE_H__

#include <string>
#include <iostream>

#include "spdlog/spdlog.h"

class CliCore
{
public:
    // Function to download a file using libcurl
    bool DownloadFile(const std::string& url, const std::string& outputPath);
};

#endif