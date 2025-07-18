#include "fanyi_cli.h"
#include "spdlog/spdlog.h"


  std::string FanyiCli::GetHelp()
  {
    return "FanyiCli";
  }

bool FanyiCli::Run(std::vector<std::string> args)
{
    if (args.size() > 0) 
    {
        std::string text;
        for (int i=0; i<args.size(); i++) {
            text.append(args[i]);
            if (i<args.size()-1) {
            text.append(" ");
            }
        }
        std::string text_encode = curl_escape(text.c_str(), text.size());
        std::string fanyi_url = "https://translate.appworlds.cn?from=en&to=zh-CN&text=";
        fanyi_url.append(text_encode);

         SPDLOG_INFO("{}",fanyi_url);
        std::string fanyi_text;
        int fanyi_code = CliCore::GetCliCore().Get(fanyi_url, fanyi_text);
        SPDLOG_INFO("[{}] {}",fanyi_code,fanyi_text);
        return true;
    }
    
    SPDLOG_WARN("Translate failed.");

    return false;
}

