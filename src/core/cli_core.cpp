#include <curl/curl.h>
#include <cstdio> // For fopen, fwrite, fclose
#include <memory>

#include "cli_core.h"

CliCore CliCore::GetCliCore()
{
    static CliCore cliCore;
    return cliCore;
}

// 定义回调函数，用于将下载的数据写入本地文件
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}

int CliCore::DownloadFile(const std::string& url, const std::string& outputPath)
{
     CURL *curl = curl_easy_init();
    FILE *fp = fopen(outputPath.c_str(), "wb");  // 打开一个文件用于保存下载的数据

    if (curl && fp) {
        // 设置下载选项
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        // --- Security Options for HTTPS ---
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // Verify the server's SSL certificate
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        // Verify the server's hostname against the certificate
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        // 执行下载请求
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "下载失败: %s\n", curl_easy_strerror(res));
            fclose(fp);
            curl_easy_cleanup(curl);
            return -1;
        }

        fclose(fp);
    } else {
        fprintf(stderr, "初始化失败\n");
        if (fp) {
            fclose(fp);
        }
        if (curl) {
            curl_easy_cleanup(curl);
        }
        return -1;
    }

    curl_easy_cleanup(curl);
    return 0;
}