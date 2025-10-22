#include "config_manager.h"
#include "cli_core.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iterator>

ConfigManager& ConfigManager::GetInstance()
{
    static ConfigManager instance;
    return instance;
}

bool ConfigManager::LoadConfig(const std::string& config_path)
{
    if (!config_path.empty())
    {
        config_path_ = config_path;
    }
    else
    {
        config_path_ = GetDefaultConfigPath();
    }
    
    try
    {
        // 使用标准文件系统读取配置
        std::ifstream file(config_path_);
        if (file.is_open())
        {
            std::string content((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
            config_ = json::parse(content);
            loaded_ = true;
            
            SPDLOG_INFO("Configuration loaded from: {}", config_path_);
            return true;
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_WARN("Failed to load config from {}: {}", config_path_, e.what());
    }
    
    // 如果加载失败，使用默认配置
    SetDefaults();
    loaded_ = true;
    return false;
}

bool ConfigManager::SaveConfig(const std::string& config_path)
{
    if (!config_path.empty())
    {
        config_path_ = config_path;
    }
    
    try
    {
        std::string content = config_.dump(4);
        std::ofstream file(config_path_);
        
        if (file.is_open())
        {
            file << content;
            SPDLOG_INFO("Configuration saved to: {}", config_path_);
            return true;
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_ERROR("Failed to save config to {}: {}", config_path_, e.what());
    }
    
    return false;
}

std::string ConfigManager::GetString(const std::string& key, const std::string& default_value) const
{
    const_cast<ConfigManager*>(this)->EnsureLoaded();
    
    try
    {
        if (config_.contains(key) && config_[key].is_string())
        {
            return config_[key].get<std::string>();
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_WARN("Error getting string config '{}': {}", key, e.what());
    }
    
    return default_value;
}

int ConfigManager::GetInt(const std::string& key, int default_value) const
{
    const_cast<ConfigManager*>(this)->EnsureLoaded();
    
    try
    {
        if (config_.contains(key) && config_[key].is_number_integer())
        {
            return config_[key].get<int>();
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_WARN("Error getting int config '{}': {}", key, e.what());
    }
    
    return default_value;
}

bool ConfigManager::GetBool(const std::string& key, bool default_value) const
{
    const_cast<ConfigManager*>(this)->EnsureLoaded();
    
    try
    {
        if (config_.contains(key) && config_[key].is_boolean())
        {
            return config_[key].get<bool>();
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_WARN("Error getting bool config '{}': {}", key, e.what());
    }
    
    return default_value;
}

void ConfigManager::SetString(const std::string& key, const std::string& value)
{
    EnsureLoaded();
    config_[key] = value;
}

void ConfigManager::SetInt(const std::string& key, int value)
{
    EnsureLoaded();
    config_[key] = value;
}

void ConfigManager::SetBool(const std::string& key, bool value)
{
    EnsureLoaded();
    config_[key] = value;
}

bool ConfigManager::HasKey(const std::string& key) const
{
    const_cast<ConfigManager*>(this)->EnsureLoaded();
    return config_.contains(key);
}

void ConfigManager::RemoveKey(const std::string& key)
{
    EnsureLoaded();
    if (config_.contains(key))
    {
        config_.erase(key);
    }
}

std::string ConfigManager::GetDefaultConfigPath() const
{
    std::string user_dir = CliCore::GetCliCore().GetUserDirectory();
    return user_dir + "/z-cli-config.json";
}

void ConfigManager::EnsureLoaded()
{
    if (!loaded_)
    {
        LoadConfig();
    }
}

void ConfigManager::SetDefaults()
{
    config_ = json::object();
    
    // 应用程序默认配置
    config_["app"]["version"] = "1.0.0";
    config_["app"]["log_level"] = "info";
    config_["app"]["interactive_mode"] = true;
    
    // 网络默认配置
    config_["network"]["timeout"] = 30;
    config_["network"]["retry_count"] = 3;
    
    // 翻译服务默认配置
    config_["fanyi"]["default_from"] = "auto";
    config_["fanyi"]["default_to"] = "zh-CN";
    config_["fanyi"]["service_url"] = "https://translate.appworlds.cn";
    
    // 文件系统默认配置
    config_["filesystem"]["default_encoding"] = "utf-8";
    config_["filesystem"]["backup_enabled"] = true;
    
    SPDLOG_INFO("Default configuration applied");
}