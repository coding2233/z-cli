#include "../tests/test_framework.h"
#include "../src/core/config_manager.h"
#include "../src/core/error_handler.h"
#include "../src/cli.h"
#include <memory>
#include <string>

// 测试配置管理器
TEST(ConfigManagerTest)
{
    auto& config = ConfigManager::GetInstance();
    
    // 测试默认值
    ASSERT_EQ(config.GetString("nonexistent", "default"), "default");
    ASSERT_EQ(config.GetInt("nonexistent", 42), 42);
    ASSERT_EQ(config.GetBool("nonexistent", true), true);
    
    // 测试设置和获取
    config.SetString("test_string", "hello");
    config.SetInt("test_int", 123);
    config.SetBool("test_bool", true);
    
    ASSERT_EQ(config.GetString("test_string"), "hello");
    ASSERT_EQ(config.GetInt("test_int"), 123);
    ASSERT_EQ(config.GetBool("test_bool"), true);
    
    // 测试键存在性检查
    ASSERT_TRUE(config.HasKey("test_string"));
    ASSERT_FALSE(config.HasKey("nonexistent"));
    
    // 测试删除键
    config.RemoveKey("test_string");
    ASSERT_FALSE(config.HasKey("test_string"));
    ASSERT_EQ(config.GetString("test_string", "default"), "default");
    
    return true;
}

// 测试错误处理
TEST(ErrorHandlerTest)
{
    auto& error_handler = ErrorHandler::GetInstance();
    
    // 测试已知异常
    int result = error_handler.HandleException(ConfigException("test config error"));
    ASSERT_EQ(result, 2); // 配置错误返回码
    
    result = error_handler.HandleException(FileSystemException("test file error"));
    ASSERT_EQ(result, 3); // 文件系统错误返回码
    
    result = error_handler.HandleException(NetworkException("test network error"));
    ASSERT_EQ(result, 4); // 网络错误返回码
    
    result = error_handler.HandleException(ValidationException("test validation error"));
    ASSERT_EQ(result, 5); // 验证错误返回码
    
    result = error_handler.HandleException(std::runtime_error("test generic error"));
    ASSERT_EQ(result, 1); // 通用错误返回码
    
    return true;
}

// 测试CLI基类
TEST(CliBaseTest)
{
    class TestCli : public Cli
    {
    public:
        TestCli(const std::string& name, const std::string& help_text) 
            : Cli(name, help_text) {}
        
        void SetupOptions() override
        {
            options_.add_options()
                ("h,help", "Print help");
        }
        
        bool Run(cxxopts::ParseResult result) override
        {
            return true;
        }
    };
    
    TestCli test_cli("test", "test command");
    
    ASSERT_EQ(test_cli.GetHelpText(), "test command");
    
    // 测试选项访问
    auto& options = test_cli.GetOptions();
    ASSERT_TRUE(options.allow_unrecognised_options());
    
    return true;
}

// 主测试函数
int main()
{
    std::cout << "=== z-cli Unit Tests ===" << std::endl;
    
    bool all_passed = TestFramework::GetInstance().RunAllTests();
    
    if (all_passed)
    {
        std::cout << "\n✓ All tests passed!" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "\n✗ Some tests failed!" << std::endl;
        return 1;
    }
}