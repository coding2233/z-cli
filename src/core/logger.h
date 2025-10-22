#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include <mutex>
#include "spdlog/spdlog.h"

// 日志级别枚举
enum class LogLevel
{
    Trace = 0,
    Debug = 1,
    Info = 2,
    Warn = 3,
    Error = 4,
    Critical = 5,
    Off = 6
};

// 日志事件结构
struct LogEvent
{
    LogLevel level;
    std::string message;
    std::string file;
    int line;
    std::string function;
    std::chrono::system_clock::time_point timestamp;
    
    LogEvent(LogLevel lvl, const std::string& msg, const std::string& f, int l, const std::string& func)
        : level(lvl), message(msg), file(f), line(l), function(func)
        , timestamp(std::chrono::system_clock::now())
    {}
};

// 日志格式化器接口
class ILogFormatter
{
public:
    virtual ~ILogFormatter() = default;
    virtual std::string Format(const LogEvent& event) = 0;
};

// 默认日志格式化器
class DefaultLogFormatter : public ILogFormatter
{
public:
    std::string Format(const LogEvent& event) override;
    
private:
    std::string GetLevelString(LogLevel level);
    std::string FormatTime(const std::chrono::system_clock::time_point& timestamp);
};

// 日志输出器接口
class ILogAppender
{
public:
    virtual ~ILogAppender() = default;
    virtual void Append(const LogEvent& event) = 0;
    virtual void Flush() = 0;
};

// 控制台日志输出器
class ConsoleLogAppender : public ILogAppender
{
public:
    ConsoleLogAppender(std::shared_ptr<ILogFormatter> formatter = nullptr);
    void Append(const LogEvent& event) override;
    void Flush() override;

private:
    std::shared_ptr<ILogFormatter> formatter_;
    std::mutex mutex_;
};

// 文件日志输出器
class FileLogAppender : public ILogAppender
{
public:
    FileLogAppender(const std::string& filename, 
                   std::shared_ptr<ILogFormatter> formatter = nullptr);
    ~FileLogAppender();
    
    void Append(const LogEvent& event) override;
    void Flush() override;
    
    void SetMaxFileSize(size_t max_size) { max_file_size_ = max_size; }
    void SetMaxFiles(int max_files) { max_files_ = max_files; }

private:
    void CheckAndRotateFile();
    
    std::string filename_;
    std::ofstream file_stream_;
    std::shared_ptr<ILogFormatter> formatter_;
    std::mutex mutex_;
    size_t max_file_size_;
    int max_files_;
    size_t current_file_size_;
};

// 高级日志管理器
class Logger
{
public:
    static Logger& GetInstance();
    
    // 初始化日志系统
    void Initialize(const std::string& config_file = "");
    
    // 设置日志级别
    void SetLogLevel(LogLevel level);
    LogLevel GetLogLevel() const { return level_; }
    
    // 添加输出器
    void AddAppender(std::shared_ptr<ILogAppender> appender);
    
    // 移除输出器
    void RemoveAppender(std::shared_ptr<ILogAppender> appender);
    
    // 清除所有输出器
    void ClearAppenders();
    
    // 日志记录方法
    void Log(LogLevel level, const std::string& message, 
             const std::string& file = "", int line = 0, const std::string& function = "");
    
    // 便捷方法
    void Trace(const std::string& message, const std::string& file = "", int line = 0, const std::string& function = "");
    void Debug(const std::string& message, const std::string& file = "", int line = 0, const std::string& function = "");
    void Info(const std::string& message, const std::string& file = "", int line = 0, const std::string& function = "");
    void Warn(const std::string& message, const std::string& file = "", int line = 0, const std::string& function = "");
    void Error(const std::string& message, const std::string& file = "", int line = 0, const std::string& function = "");
    void Critical(const std::string& message, const std::string& file = "", int line = 0, const std::string& function = "");
    
    // 刷新所有输出器
    void Flush();
    
    // 从配置文件加载设置
    void LoadFromConfig(const std::string& config_file);
    
    // 启用/禁用spdlog集成
    void EnableSpdlogIntegration(bool enable) { spdlog_integration_ = enable; }

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    LogLevel level_;
    std::vector<std::shared_ptr<ILogAppender>> appenders_;
    std::mutex mutex_;
    bool spdlog_integration_ = true;
    
    // 转换为spdlog级别
    spdlog::level::level_enum ToSpdlogLevel(LogLevel level);
};

// 日志宏定义
#define LOG_TRACE(message) \
    Logger::GetInstance().Trace(message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_DEBUG(message) \
    Logger::GetInstance().Debug(message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_INFO(message) \
    Logger::GetInstance().Info(message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_WARN(message) \
    Logger::GetInstance().Warn(message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_ERROR(message) \
    Logger::GetInstance().Error(message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_CRITICAL(message) \
    Logger::GetInstance().Critical(message, __FILE__, __LINE__, __FUNCTION__)

// 条件日志宏
#define LOG_DEBUG_IF(condition, message) \
    do { if (condition) LOG_DEBUG(message); } while(0)

#define LOG_ERROR_IF(condition, message) \
    do { if (condition) LOG_ERROR(message); } while(0)

#endif // __LOGGER_H__