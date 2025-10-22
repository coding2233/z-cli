#ifndef __CONFIG_MANAGER_H__
#define __CONFIG_MANAGER_H__

#include <string>
#include <unordered_map>
#include <memory>
#include "vfspp/VFS.h"
#include "json.hpp"

using json = nlohmann::json;

class ConfigManager
{
public:
    static ConfigManager& GetInstance();
    
    // 加载配置文件
    bool LoadConfig(const std::string& config_path = "");
    
    // 保存配置文件
    bool SaveConfig(const std::string& config_path = "");
    
    // 获取字符串配置值
    std::string GetString(const std::string& key, const std::string& default_value = "") const;
    
    // 获取整数配置值
    int GetInt(const std::string& key, int default_value = 0) const;
    
    // 获取布尔配置值
    bool GetBool(const std::string& key, bool default_value = false) const;
    
    // 设置字符串配置值
    void SetString(const std::string& key, const std::string& value);
    
    // 设置整数配置值
    void SetInt(const std::string& key, int value);
    
    // 设置布尔配置值
    void SetBool(const std::string& key, bool value);
    
    // 检查配置键是否存在
    bool HasKey(const std::string& key) const;
    
    // 删除配置键
    void RemoveKey(const std::string& key);
    
    // 获取默认配置文件路径
    std::string GetDefaultConfigPath() const;

private:
    ConfigManager() = default;
    ~ConfigManager() = default;
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    
    json config_;
    std::string config_path_;
    bool loaded_ = false;
    
    // 确保配置已加载
    void EnsureLoaded();
    
    // 设置默认配置值
    void SetDefaults();
};

#endif // __CONFIG_MANAGER_H__