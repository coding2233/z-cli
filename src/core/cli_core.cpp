#include <curl/curl.h>
#include <cstdio> // For fopen, fwrite, fclose

#include "cli_core.h"

// Callback function to write received data into a file
static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
    return written;
}

bool CliCore::DownloadFile(const std::string& url, const std::string& outputPath)
{
    CURL *curl = curl_easy_init();
    FILE *fp = fopen(outputPath.c_str(), "wb");  //打开一个文件用于保存下载的数据

    if (curl && fp) {
        //http://speedtest.tele2.net/1MB.zip
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Download failed: %s\n", curl_easy_strerror(res));
        }

        fclose(fp);
    } else {
        fprintf(stderr, "Init failed.\n");
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return false;
}