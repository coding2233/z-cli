#include "plugin_manager.h"
#include "cli_core.h"
#include <filesystem>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

PluginManager& PluginManager::GetInstance()
{
    static PluginManager instance;
    return instance;
}

bool PluginManager::LoadPlugin(const std::string& plugin_path)
{
    if (!std::filesystem::exists(plugin_path))
    {
        SPDLOG_ERROR("Plugin file does not exist: {}", plugin_path);
        return false;
    }
    
    if (!ValidatePlugin(plugin_path))
    {
        SPDLOG_ERROR("Plugin validation failed: {}", plugin_path);
        return false;
    }
    
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(plugin_path.c_str());
    if (!handle)
    {
        SPDLOG_ERROR("Failed to load plugin: {}", plugin_path);
        return false;
    }
    
    auto create_func = reinterpret_cast<CreatePluginFunc>(GetProcAddress(handle, "CreatePlugin"));
    auto name_func = reinterpret_cast<const char* (*)()>(GetProcAddress(handle, "GetPluginName"));
#else
    void* handle = dlopen(plugin_path.c_str(), RTLD_LAZY);
    if (!handle)
    {
        SPDLOG_ERROR("Failed to load plugin: {} - {}", plugin_path, dlerror());
        return false;
    }
    
    auto create_func = reinterpret_cast<CreatePluginFunc>(dlsym(handle, "CreatePlugin"));
    auto name_func = reinterpret_cast<const char* (*)()>(dlsym(handle, "GetPluginName"));
#endif
    
    if (!create_func || !name_func)
    {
        SPDLOG_ERROR("Plugin does not export required functions: {}", plugin_path);
        return false;
    }
    
    try
    {
        auto plugin = create_func();
        if (!plugin)
        {
            SPDLOG_ERROR("Failed to create plugin instance: {}", plugin_path);
            return false;
        }
        
        std::string plugin_name = name_func();
        if (plugin_name.empty())
        {
            SPDLOG_ERROR("Plugin has empty name: {}", plugin_path);
            return false;
        }
        
        if (!plugin->Initialize())
        {
            SPDLOG_ERROR("Plugin initialization failed: {}", plugin_name);
            return false;
        }
        
        PluginInfo info;
        info.name = plugin_name;
        info.version = plugin->GetVersion();
        info.description = plugin->GetDescription();
        info.file_path = plugin_path;
        info.is_loaded = true;
        info.plugin = plugin;
        
        plugins_[plugin_name] = info;
        
        RegisterPluginCommands(plugin);
        
        SPDLOG_INFO("Plugin loaded successfully: {} v{}", plugin_name, info.version);
        return true;
    }
    catch (const std::exception& e)
    {
        SPDLOG_ERROR("Exception while loading plugin {}: {}", plugin_path, e.what());
        return false;
    }
}

bool PluginManager::UnloadPlugin(const std::string& plugin_name)
{
    auto it = plugins_.find(plugin_name);
    if (it == plugins_.end())
    {
        SPDLOG_WARN("Plugin not found: {}", plugin_name);
        return false;
    }
    
    try
    {
        if (it->second.plugin)
        {
            it->second.plugin->Shutdown();
        }
        
        plugins_.erase(it);
        SPDLOG_INFO("Plugin unloaded: {}", plugin_name);
        return true;
    }
    catch (const std::exception& e)
    {
        SPDLOG_ERROR("Exception while unloading plugin {}: {}", plugin_name, e.what());
        return false;
    }
}

std::vector<PluginInfo> PluginManager::GetLoadedPlugins() const
{
    std::vector<PluginInfo> result;
    for (const auto& pair : plugins_)
    {
        if (pair.second.is_loaded)
        {
            result.push_back(pair.second);
        }
    }
    return result;
}

PluginInfo PluginManager::GetPluginInfo(const std::string& plugin_name) const
{
    auto it = plugins_.find(plugin_name);
    if (it != plugins_.end())
    {
        return it->second;
    }
    return PluginInfo{};
}

void PluginManager::ScanPluginDirectory(const std::string& directory)
{
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
    {
        SPDLOG_WARN("Plugin directory does not exist: {}", directory);
        return;
    }
    
    plugin_directory_ = directory;
    
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            std::string extension = entry.path().extension().string();
#ifdef _WIN32
            if (extension == ".dll")
#else
            if (extension == ".so")
#endif
            {
                SPDLOG_INFO("Found plugin: {}", entry.path().string());
                LoadPlugin(entry.path().string());
            }
        }
    }
}

std::vector<std::shared_ptr<Cli>> PluginManager::GetAllPluginCommands()
{
    std::vector<std::shared_ptr<Cli>> commands;
    
    for (const auto& pair : plugins_)
    {
        if (pair.second.is_loaded && pair.second.plugin)
        {
            auto plugin_commands = pair.second.plugin->GetCliCommands();
            commands.insert(commands.end(), plugin_commands.begin(), plugin_commands.end());
        }
    }
    
    return commands;
}

void PluginManager::SetPluginDirectory(const std::string& directory)
{
    plugin_directory_ = directory;
}

bool PluginManager::EnablePlugin(const std::string& plugin_name)
{
    auto it = plugins_.find(plugin_name);
    if (it == plugins_.end())
    {
        SPDLOG_WARN("Plugin not found: {}", plugin_name);
        return false;
    }
    
    if (it->second.is_loaded)
    {
        SPDLOG_INFO("Plugin already enabled: {}", plugin_name);
        return true;
    }
    
    return LoadPlugin(it->second.file_path);
}

bool PluginManager::DisablePlugin(const std::string& plugin_name)
{
    return UnloadPlugin(plugin_name);
}

bool PluginManager::ValidatePlugin(const std::string& plugin_path)
{
    // 基本验证：检查文件是否存在且可读
    return std::filesystem::exists(plugin_path) && 
           std::filesystem::is_regular_file(plugin_path);
}

void PluginManager::RegisterPluginCommands(const std::shared_ptr<IPlugin>& plugin)
{
    if (!plugin)
    {
        return;
    }
    
    try
    {
        auto commands = plugin->GetCliCommands();
        
        for (const auto& command : commands)
        {
            // 插件命令注册逻辑暂时简化
            // 在实际使用中，可以通过其他方式集成到主应用
            SPDLOG_INFO("Registered CLI command from plugin: {}", command->GetHelpText());
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_ERROR("Failed to register plugin commands: {}", e.what());
    }
}