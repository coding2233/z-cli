#include "update_cli.h"
#include "IFileSystem.h"
#include "spdlog/spdlog.h"
#include <cstdlib>
#include <future>

bool UpdateCli::Run(std::vector<std::string> args) {
  SPDLOG_INFO("UpdateCli::Run");

  if (args.size() == 2) {
    Update(args[0], args[1]);
  } else {
    Download();
  }
  return true;
}

void UpdateCli::Download() {
  std::string spile_char = "/";
#if _WIN32
  spile_char = "\\";
#endif

  // std::string url = "http://speedtest.tele2.net/1MB.zip";
  std::string url =
      "https://github.com/coding2233/z-cli/releases/download/nightly/";
  std::string file_name;
#if _WIN32
  file_name = "z-cli-windows-x64.zip";
#elif __APPLE__
  file_name = "z-cli-macosx-arm64.zip";
#elif __linux__
  file_name = "z-cli-linux-x86_64.zip";
#endif
  url.append(file_name);
  std::string download_file_path = CliCore::GetCliCore()
                                       .GetUserDirectory()
                                       .append(spile_char)
                                       .append(file_name);
  SPDLOG_INFO("Download url:{}", url, download_file_path);
  int ret = CliCore::GetCliCore().DownloadFile(url, download_file_path);
  SPDLOG_INFO("Download result:{} file_name:{}", ret, download_file_path);

  if (ret == 0) {

    IFileSystemPtr update_fs =
        std::make_unique<ZipFileSystem>(download_file_path);
    update_fs->Initialize();
    auto file_list = update_fs->FileList();

    // 挂载下载的文件到/update下
    CliCore::GetCliCore().GetVirtualFileSystem()->AddFileSystem(
        "/update", std::move(update_fs));

    // 复制z-cli
    // 复制/update -> /app下进行更新
    std::string updater_name;
    for (auto iter = file_list.begin(); iter != file_list.end(); iter++) {
      if (iter->first.find("/z-cli") != std::string::npos) {
        SPDLOG_INFO("{}", iter->first);

        std::string src = "/update" + iter->first;
        updater_name = "z-cli-updater";
        if (iter->first.length() > 6) {
          iter->first.substr(6);
        }
        CliCore::GetCliCore().VFSCopyFile(src, "/" + updater_name);
      }
    }

    // 运行程序
    std::string updater_basepath = CliCore::GetCliCore().GetUserDirectory();
    std::string app_basepath = CliCore::GetCliCore().GetAppPath();
    std::string updater_path = updater_basepath;

    std::string cmd = updater_basepath.append(spile_char)
                          .append(updater_name)
                          .append(" update ")
                          .append(download_file_path)
                          .append(" ")
                          .append(app_basepath);
    SPDLOG_INFO("cmd: {}", cmd);
    auto cmd_result =
        std::async(std::launch::async, [&cmd]() { std::system(cmd.c_str()); });

    CliCore::GetCliCore().WaitSleep(1);
    exit(0);
  }
}

void UpdateCli::Update(std::string zip_file, std::string bin_path) {
  SPDLOG_INFO("UpdateCli::Update {} {}", zip_file, bin_path);
  CliCore::GetCliCore().WaitSleep(1);
  IFileSystemPtr update_fs = std::make_unique<ZipFileSystem>(zip_file);
  update_fs->Initialize();
  auto file_list = update_fs->FileList();
  // 挂载下载的文件到/update下
  CliCore::GetCliCore().GetVirtualFileSystem()->AddFileSystem(
      "/update", std::move(update_fs));

  // 挂在/update-app
  std::string update_app_name = std::string("/update-app");
  CliCore::GetCliCore().AddNativeFileSystem(update_app_name, bin_path);

  // 复制/update -> /app下进行更新
  for (auto iter = file_list.begin(); iter != file_list.end(); iter++) {
    SPDLOG_INFO("{}", iter->first);

    std::string src = "/update" + iter->first;
    std::string dest = "/update-app" + iter->first;
    CliCore::GetCliCore().VFSCopyFile(src, dest);
  }
  SPDLOG_INFO("Update Success.");
  exit(0);
}