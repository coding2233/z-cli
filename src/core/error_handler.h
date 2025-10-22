#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__

#include <string>
#include <exception>
#include <memory>

// 自定义异常类
class CliException : public std::exception
{
public:
    explicit CliException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override { return message_.c_str(); }

private:
    std::string message_;
};

class ConfigException : public CliException
{
public:
    explicit ConfigException(const std::string& message) : CliException("Config error: " + message) {}
};

class FileSystemException : public CliException
{
public:
    explicit FileSystemException(const std::string& message) : CliException("File system error: " + message) {}
};

class NetworkException : public CliException
{
public:
    explicit NetworkException(const std::string& message) : CliException("Network error: " + message) {}
};

class ValidationException : public CliException
{
public:
    explicit ValidationException(const std::string& message) : CliException("Validation error: " + message) {}
};

class ErrorHandler
{
public:
    static ErrorHandler& GetInstance();
    
    // 处理异常并返回适当的退出码
    int HandleException(const std::exception& e);
    
    // 处理未知异常
    int HandleUnknownException();
    
    // 记录错误信息
    void LogError(const std::string& context, const std::exception& e);
    
    // 设置是否显示详细错误信息
    void SetVerbose(bool verbose) { verbose_ = verbose; }
    
    // 设置是否在错误时显示堆栈跟踪
    void SetShowStackTrace(bool show) { show_stack_trace_ = show; }

private:
    ErrorHandler() = default;
    ~ErrorHandler() = default;
    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;
    
    bool verbose_ = false;
    bool show_stack_trace_ = false;
    
    // 获取异常类型名称
    std::string GetExceptionTypeName(const std::exception& e);
};

// 错误处理宏
#define TRY_EXECUTE(expression) \
    try { \
        expression; \
    } catch (const std::exception& e) { \
        return ErrorHandler::GetInstance().HandleException(e); \
    } catch (...) { \
        return ErrorHandler::GetInstance().HandleUnknownException(); \
    }

#define TRY_EXECUTE_RETURN(expression, default_return) \
    try { \
        return expression; \
    } catch (const std::exception& e) { \
        ErrorHandler::GetInstance().HandleException(e); \
        return default_return; \
    } catch (...) { \
        ErrorHandler::GetInstance().HandleUnknownException(); \
        return default_return; \
    }

#endif // __ERROR_HANDLER_H__