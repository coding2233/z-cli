#include "error_handler.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <typeinfo>

ErrorHandler& ErrorHandler::GetInstance()
{
    static ErrorHandler instance;
    return instance;
}

int ErrorHandler::HandleException(const std::exception& e)
{
    LogError("Application", e);
    
    if (verbose_)
    {
        std::cerr << "Error [" << GetExceptionTypeName(e) << "]: " << e.what() << std::endl;
        
        if (show_stack_trace_)
        {
            // 在实际项目中，这里可以实现堆栈跟踪功能
            std::cerr << "Stack trace not available in this build." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    // 根据异常类型返回不同的退出码
    if (dynamic_cast<const ConfigException*>(&e))
    {
        return 2; // 配置错误
    }
    else if (dynamic_cast<const FileSystemException*>(&e))
    {
        return 3; // 文件系统错误
    }
    else if (dynamic_cast<const NetworkException*>(&e))
    {
        return 4; // 网络错误
    }
    else if (dynamic_cast<const ValidationException*>(&e))
    {
        return 5; // 验证错误
    }
    else
    {
        return 1; // 通用错误
    }
}

int ErrorHandler::HandleUnknownException()
{
    SPDLOG_ERROR("Unknown exception occurred");
    std::cerr << "An unknown error occurred." << std::endl;
    return 1;
}

void ErrorHandler::LogError(const std::string& context, const std::exception& e)
{
    SPDLOG_ERROR("[{}] {}: {}", context, GetExceptionTypeName(e), e.what());
}

std::string ErrorHandler::GetExceptionTypeName(const std::exception& e)
{
    return typeid(e).name();
}