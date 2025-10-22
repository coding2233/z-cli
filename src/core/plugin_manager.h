#ifndef __PLUGIN_MANAGER_H__
#define __PLUGIN_MANAGER_H__

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../cli.h"

// 插件接口
class IPlugin
{
public:
    virtual ~IPlugin() = default;
    
    // 插件名称
    virtual std::string GetName() const = 0;
    
    // 插件版本
    virtual std::string GetVersion() const = 0;
    
    // 插件描述
    virtual std::string GetDescription() const = 0;
    
    // 插件初始化
    virtual bool Initialize() = 0;
    
    // 插件清理
    virtual void Shutdown() = 0;
    
    // 获取插件提供的CLI命令
    virtual std::vector<std::shared_ptr<Cli>> GetCliCommands() = 0;
};

// 插件信息
struct PluginInfo
{
    std::string name;
    std::string version;
    std::string description;
    std::string file_path;
    bool is_loaded = false;
    std::shared_ptr<IPlugin> plugin;
};

class PluginManager
{
public:
    static PluginManager& GetInstance();
    
    // 加载插件
    bool LoadPlugin(const std::string& plugin_path);
    
    // 卸载插件
    bool UnloadPlugin(const std::string& plugin_name);
    
    // 获取所有已加载的插件
    std::vector<PluginInfo> GetLoadedPlugins() const;
    
    // 获取插件信息
    PluginInfo GetPluginInfo(const std::string& plugin_name) const;
    
    // 扫描插件目录
    void ScanPluginDirectory(const std::string& directory);
    
    // 获取所有插件提供的CLI命令
    std::vector<std::shared_ptr<Cli>> GetAllPluginCommands();
    
    // 设置插件目录
    void SetPluginDirectory(const std::string& directory);
    
    // 启用/禁用插件
    bool EnablePlugin(const std::string& plugin_name);
    bool DisablePlugin(const std::string& plugin_name);

private:
    PluginManager() = default;
    ~PluginManager() = default;
    PluginManager(const PluginManager&) = delete;
    PluginManager& operator=(const PluginManager&) = delete;
    
    std::unordered_map<std::string, PluginInfo> plugins_;
    std::string plugin_directory_;
    
    // 验证插件
    bool ValidatePlugin(const std::string& plugin_path);
    
    // 注册插件命令
    void RegisterPluginCommands(const std::shared_ptr<IPlugin>& plugin);
};

// 插件创建函数类型
using CreatePluginFunc = std::shared_ptr<IPlugin>(*)();

// 插件导出宏
#define EXPORT_PLUGIN(PluginClass) \
    extern "C" { \
        std::shared_ptr<IPlugin> CreatePlugin() { \
            return std::make_shared<PluginClass>(); \
        } \
        \
        const char* GetPluginName() { \
            return #PluginClass; \
        } \
    }

#endif // __PLUGIN_MANAGER_H__
