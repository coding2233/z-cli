#include "fanyi_cli.h"
#include "spdlog/spdlog.h"
#include <iostream>

void FanyiCli::SetupOptions()
{
    options_.add_options()
        ("h,help", "Print help")
        ("t,text", "Text to translate", cxxopts::value<std::vector<std::string>>());

    options_.parse_positional({"text"});
}

bool FanyiCli::Run(cxxopts::ParseResult result)
{
    if (result.count("help"))
    {
        std::cout << options_.help() << std::endl;
        return true;
    }

    if (result.count("text"))
    {
        std::string text_to_translate;
        const auto& text_vector = result["text"].as<std::vector<std::string>>();
        for (size_t i = 0; i < text_vector.size(); ++i)
        {
            text_to_translate += text_vector[i];
            if (i < text_vector.size() - 1)
            {
                text_to_translate += " ";
            }
        }

        std::string fanyi_url = "https://translate.appworlds.cn";
        std::string text_encode = curl_escape(text_to_translate.c_str(), text_to_translate.size());
        
        // Simple UTF-8 detection - check if text contains non-ASCII characters
        bool is_utf8 = false;
        for (char c : text_to_translate) {
            if (static_cast<unsigned char>(c) > 127) {
                is_utf8 = true;
                break;
            }
        }
        
        if (is_utf8)
        {
            fanyi_url.append("?from=zh-CN&to=en");
        }
        else
        {
            fanyi_url.append("?from=en&to=zh-CN");
        }
        fanyi_url.append("&text=").append(text_encode);

        SPDLOG_INFO("url: {}", fanyi_url);
        std::string fanyi_text;
        std::string fanyi_output_text;
        int fanyi_code = CliCore::GetCliCore().Get(fanyi_url, fanyi_text);
        if (fanyi_code == 0)
        {
            auto fanyi_json = nlohmann::json::parse(fanyi_text);
            fanyi_output_text = fanyi_json["data"];
        }
        FanyiPrint("translate.appworlds.cn", fanyi_output_text);
        return true;
    }
    else
    {
        std::cout << options_.help() << std::endl;
    }

    return true;
}

void FanyiCli::FanyiPrint(std::string name, std::string output)
{
    std::cout << ">> " << name << std::endl;
    std::cout << output << std::endl;
}

