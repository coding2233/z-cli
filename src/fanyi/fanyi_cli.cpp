#include "fanyi_cli.h"
#include "spdlog/spdlog.h"
#include <iostream>


  std::string FanyiCli::GetHelp()
  {
    return "FanyiCli";
  }

bool FanyiCli::Run(std::vector<std::string> args)
{
    if (args.size() > 0) 
    {
        std::string fanyi_url = "https://translate.appworlds.cn";

        std::string text;
        for (int i=0; i<args.size(); i++) {
            text.append(args[i]);
            if (i<args.size()-1) {
            text.append(" ");
            }
        }
        std::string text_encode = curl_escape(text.c_str(), text.size());
        SPDLOG_INFO("text {} {}",text,text_encode);
        // bool is_utf8 = CliCore::GetCliCore().VaildUTF8String(text_encode);
        bool is_utf8 = false;
        if (is_utf8) 
        {
            fanyi_url.append("?from=zh-CN&to=en");
        }
        else {
            fanyi_url.append("?from=en&to=zh-CN");
        }
        fanyi_url.append("&text=").append(text_encode);

        SPDLOG_INFO("url: {}",fanyi_url);
        std::string fanyi_text;
        std::string fanyi_output_text;
        int fanyi_code = CliCore::GetCliCore().Get(fanyi_url, fanyi_text);
        if (fanyi_code == 0) {
            auto fanyi_json = nlohmann::json::parse(fanyi_text);
            fanyi_output_text = fanyi_json["data"];
        }
        FanyiPrint("translate.appworlds.cn",fanyi_output_text);;
        return true;
    }
    
    SPDLOG_WARN("Translate failed.");

    return false;
}

void FanyiCli::FanyiPrint(std::string name,std::string output)
{
    std::cout<< ">> "<<name<<std::endl;
    std::cout<<output<<std::endl;
}

