#include <filesystem>
#include <memory>

#include "cli_core.h"
#include "spdlog/spdlog.h"
#include "utf8/core.h"
#include "vfspp/IFile.h"
#include "vfspp/IFileSystem.h"

#include "llama.h"
#include "ggml.h"

CliCore &CliCore::GetCliCore() {
  static CliCore cliCore;
  return cliCore;
}

// 定义回调函数，用于将下载的数据写入本地文件
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
  return fwrite(ptr, size, nmemb, (FILE *)stream);
}
static size_t http_get_write_callback(void *contents, size_t size, size_t nmemb,
                                      void *userp) {
  size_t realsize = size * nmemb;
  std::string *str = static_cast<std::string *>(userp);
  str->append(static_cast<char *>(contents), realsize);
  return realsize;
}

int CliCore::DownloadFile(const std::string &url,
                          const std::string &outputPath) {
  CURL *curl = curl_easy_init();
  FILE *fp = fopen(outputPath.c_str(), "wb"); // 打开一个文件用于保存下载的数据

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

int CliCore::Get(std::string &url, std::string &response) {
    // curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &http_get_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  } else {
    fprintf(stderr, "初始化失败\n");

  }

    CURLcode res = curl_easy_perform(curl);
    if (curl) {
      curl_easy_cleanup(curl);
    }
    return res;
}

VirtualFileSystemPtr CliCore::GetVirtualFileSystem() {
  if (!vfs_) {
    vfs_ = std::make_shared<VirtualFileSystem>();

    // 1. 映射用户主目录
    std::string userDir = GetUserDirectory();
    SPDLOG_INFO("userDir:{}", userDir);
    if (!std::filesystem::exists(userDir)) {
      SPDLOG_INFO("create_directory: {}", userDir);
      std::filesystem::create_directory(userDir);
    }
    auto userFS = std::make_unique<NativeFileSystem>(userDir);
    userFS->Initialize();
    vfs_->AddFileSystem("/", std::move(userFS));

    // 内存，用于临时文件
    auto memFS = std::make_unique<MemoryFileSystem>();
    memFS->Initialize();
    vfs_->AddFileSystem("/tmp", std::move(memFS));
  }
  return vfs_;
}

void CliCore::AddNativeFileSystem(std::string &alias, std::string &path) {
  if (!std::filesystem::exists(path)) {
    SPDLOG_INFO("create_directory: {}", path);
    std::filesystem::create_directory(path);
  }
  auto native_fs = std::make_unique<NativeFileSystem>(path);
  native_fs->Initialize();
  CliCore::GetVirtualFileSystem()->AddFileSystem(alias, std::move(native_fs));
}

bool CliCore::VFSCopyFile(std::string &src, std::string dest) {
  SPDLOG_INFO("CopyFile {} -> {}", src, dest);
  auto vfs = GetVirtualFileSystem();

  SPDLOG_INFO("VFSCopyFile Check-VFS {} {} {} {}", vfs->IsAliasRegistered("/"),
              vfs->IsAliasRegistered("/tmp"), vfs->IsAliasRegistered("/app"),
              vfs->IsAliasRegistered("/update"));

  // 流式复制大文件
  auto sourceFile = vfs->OpenFile(FileInfo(src), IFile::FileMode::Read);
  auto destFile = vfs->OpenFile(FileInfo(dest), IFile::FileMode::Write);

  bool source_valid = sourceFile && sourceFile->IsOpened();
  bool dest_valid = destFile && destFile->IsOpened();

  if (source_valid && dest_valid) {
    const size_t bufferSize = 4096; // 4KB 缓冲区
    std::vector<uint8_t> buffer(bufferSize);

    uint64_t totalCopied = 0;
    uint64_t bytesRead;

    while ((bytesRead = sourceFile->Read(buffer.data(), bufferSize)) > 0) {
      uint64_t bytesWritten = destFile->Write(buffer.data(), bytesRead);
      if (bytesWritten != bytesRead) {
        SPDLOG_ERROR("Copy file error.");
        break;
      }
      totalCopied += bytesWritten;
    }

    sourceFile->Close();
    destFile->Close();

    SPDLOG_INFO("CopyFile success. {} -> {} size:{}", src, dest, totalCopied);
    return true;
  } else {
    SPDLOG_ERROR("vfs open file error. source_valid:{} dest_vaild:{}",
                 source_valid, dest_valid);
  }
  return false;
}

// 获取不同系统的用户目录路径
std::string CliCore::GetUserDirectory() {
#ifdef _WIN32
  // Windows: C:\Users\username
  return std::string(getenv("USERPROFILE")) + "\\.z-cli";
#elif __APPLE__
  // macOS: /Users/username
  return std::string(getenv("HOME")) + "/.z-cli";
#else
  // Linux: /home/username
  return std::string(getenv("HOME")) + "/.z-cli";
#endif
}

void CliCore::SetAppPath(std::string path) { app_path_ = path; }
std::string CliCore::GetAppPath() { return app_path_; }

bool CliCore::VaildUTF8String(std::string &text)
{
    // auto result = utf8::is_valid(text);
    // return result;
    return true;
}

void CliCore::WaitSleep(int second)
{
    #if _WIN32
      Sleep(second * 1000);
    #else
      sleep(second);
    #endif
}


int CliCore::RunLlama(std::string model_path,std::string prompt)
{
    // number of layers to offload to the GPU
    int ngl = 99;
    // number of tokens to predict
    int n_predict = 32;
     // load dynamic backends

    //  ggml_backend_load_all();

    //  // initialize the model
 
    //  llama_model_params model_params = llama_model_default_params();
    //  model_params.n_gpu_layers = ngl;
 
    //  llama_model * model = llama_model_load_from_file(model_path.c_str(), model_params);
 
    //  if (model == NULL) {
    //      fprintf(stderr , "%s: error: unable to load model\n" , __func__);
    //      return 1;
    //  }
 
    //  const llama_vocab * vocab = llama_model_get_vocab(model);
    //  // tokenize the prompt
 
    //  // find the number of tokens in the prompt
    //  const int n_prompt = -llama_tokenize(vocab, prompt.c_str(), prompt.size(), NULL, 0, true, true);
 
    //  // allocate space for the tokens and tokenize the prompt
    //  std::vector<llama_token> prompt_tokens(n_prompt);
    //  if (llama_tokenize(vocab, prompt.c_str(), prompt.size(), prompt_tokens.data(), prompt_tokens.size(), true, true) < 0) {
    //      fprintf(stderr, "%s: error: failed to tokenize the prompt\n", __func__);
    //      return 1;
    //  }
 
    //  // initialize the context
 
    //  llama_context_params ctx_params = llama_context_default_params();
    //  // n_ctx is the context size
    //  ctx_params.n_ctx = n_prompt + n_predict - 1;
    //  // n_batch is the maximum number of tokens that can be processed in a single call to llama_decode
    //  ctx_params.n_batch = n_prompt;
    //  // enable performance counters
    //  ctx_params.no_perf = false;
 
    //  llama_context * ctx = llama_init_from_model(model, ctx_params);
 
    //  if (ctx == NULL) {
    //      fprintf(stderr , "%s: error: failed to create the llama_context\n" , __func__);
    //      return 1;
    //  }
 
    //  // initialize the sampler
 
    //  auto sparams = llama_sampler_chain_default_params();
    //  sparams.no_perf = false;
    //  llama_sampler * smpl = llama_sampler_chain_init(sparams);
 
    //  llama_sampler_chain_add(smpl, llama_sampler_init_greedy());
 
    //  // print the prompt token-by-token
 
    //  for (auto id : prompt_tokens) {
    //      char buf[128];
    //      int n = llama_token_to_piece(vocab, id, buf, sizeof(buf), 0, true);
    //      if (n < 0) {
    //          fprintf(stderr, "%s: error: failed to convert token to piece\n", __func__);
    //          return 1;
    //      }
    //      std::string s(buf, n);
    //      printf("%s", s.c_str());
    //  }
 
    //  // prepare a batch for the prompt
 
    //  llama_batch batch = llama_batch_get_one(prompt_tokens.data(), prompt_tokens.size());
 
    //  // main loop
 
    //  const auto t_main_start = ggml_time_us();
    //  int n_decode = 0;
    //  llama_token new_token_id;
 
    //  for (int n_pos = 0; n_pos + batch.n_tokens < n_prompt + n_predict; ) {
    //      // evaluate the current batch with the transformer model
    //      if (llama_decode(ctx, batch)) {
    //          fprintf(stderr, "%s : failed to eval, return code %d\n", __func__, 1);
    //          return 1;
    //      }
 
    //      n_pos += batch.n_tokens;
 
    //      // sample the next token
    //      {
    //          new_token_id = llama_sampler_sample(smpl, ctx, -1);
 
    //          // is it an end of generation?
    //          if (llama_vocab_is_eog(vocab, new_token_id)) {
    //              break;
    //          }
 
    //          char buf[128];
    //          int n = llama_token_to_piece(vocab, new_token_id, buf, sizeof(buf), 0, true);
    //          if (n < 0) {
    //              fprintf(stderr, "%s: error: failed to convert token to piece\n", __func__);
    //              return 1;
    //          }
    //          std::string s(buf, n);
    //          printf("%s", s.c_str());
    //          fflush(stdout);
 
    //          // prepare the next batch with the sampled token
    //          batch = llama_batch_get_one(&new_token_id, 1);
 
    //          n_decode += 1;
    //      }
    //  }
 
    //  printf("\n");
 
    //  const auto t_main_end = ggml_time_us();
 
    //  fprintf(stderr, "%s: decoded %d tokens in %.2f s, speed: %.2f t/s\n",
    //          __func__, n_decode, (t_main_end - t_main_start) / 1000000.0f, n_decode / ((t_main_end - t_main_start) / 1000000.0f));
 
    //  fprintf(stderr, "\n");
    //  llama_perf_sampler_print(smpl);
    //  llama_perf_context_print(ctx);
    //  fprintf(stderr, "\n");
 
    //  llama_sampler_free(smpl);
    //  llama_free(ctx);
    //  llama_model_free(model);
 
    return 0;
}

