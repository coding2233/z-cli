#ifndef __TEST_FRAMEWORK_H__
#define __TEST_FRAMEWORK_H__

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <chrono>
#include <sstream>
#include <iomanip>

// 简单的测试框架
class TestFramework
{
public:
    using TestFunction = std::function<bool()>;
    
    struct TestResult
    {
        std::string name;
        bool passed;
        std::string error_message;
        double execution_time_ms;
        
        TestResult(const std::string& n, bool p, const std::string& err = "", double time = 0.0)
            : name(n), passed(p), error_message(err), execution_time_ms(time)
        {}
    };
    
    static TestFramework& GetInstance()
    {
        static TestFramework instance;
        return instance;
    }
    
    // 添加测试用例
    void AddTest(const std::string& name, TestFunction test_func)
    {
        tests_.push_back({name, test_func});
    }
    
    // 运行所有测试
    bool RunAllTests()
    {
        std::cout << "Running " << tests_.size() << " tests...\n" << std::endl;
        
        int passed = 0;
        int failed = 0;
        double total_time = 0.0;
        
        for (const auto& test : tests_)
        {
            auto result = RunSingleTest(test.name, test.function);
            results_.push_back(result);
            
            if (result.passed)
            {
                passed++;
                std::cout << "[PASS] " << test.name << " (" << std::fixed << std::setprecision(2) 
                         << result.execution_time_ms << "ms)" << std::endl;
            }
            else
            {
                failed++;
                std::cout << "[FAIL] " << test.name << " (" << std::fixed << std::setprecision(2) 
                         << result.execution_time_ms << "ms)" << std::endl;
                std::cout << "       " << result.error_message << std::endl;
            }
            
            total_time += result.execution_time_ms;
        }
        
        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Total: " << tests_.size() << ", Passed: " << passed << ", Failed: " << failed << std::endl;
        std::cout << "Total execution time: " << std::fixed << std::setprecision(2) 
                 << total_time << "ms" << std::endl;
        
        return failed == 0;
    }
    
    // 运行特定测试
    bool RunTest(const std::string& name)
    {
        for (const auto& test : tests_)
        {
            if (test.name == name)
            {
                auto result = RunSingleTest(test.name, test.function);
                if (result.passed)
                {
                    std::cout << "[PASS] " << test.name << std::endl;
                }
                else
                {
                    std::cout << "[FAIL] " << test.name << ": " << result.error_message << std::endl;
                }
                return result.passed;
            }
        }
        std::cout << "Test not found: " << name << std::endl;
        return false;
    }
    
    // 获取测试结果
    const std::vector<TestResult>& GetResults() const
    {
        return results_;
    }
    
    // 清除所有测试
    void ClearTests()
    {
        tests_.clear();
        results_.clear();
    }

private:
    struct TestCase
    {
        std::string name;
        TestFunction function;
        
        TestCase(const std::string& n, TestFunction func) : name(n), function(func) {}
    };
    
    std::vector<TestCase> tests_;
    std::vector<TestResult> results_;
    
    TestResult RunSingleTest(const std::string& name, TestFunction test_func)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        
        try
        {
            bool result = test_func();
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            
            return TestResult(name, result, "", duration.count() / 1000.0);
        }
        catch (const std::exception& e)
        {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            
            return TestResult(name, false, std::string("Exception: ") + e.what(), duration.count() / 1000.0);
        }
        catch (...)
        {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            
            return TestResult(name, false, "Unknown exception", duration.count() / 1000.0);
        }
    }
};

// 测试断言宏
#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            throw std::runtime_error("Assertion failed: " #condition); \
        } \
    } while(0)

#define ASSERT_FALSE(condition) \
    do { \
        if (condition) { \
            throw std::runtime_error("Assertion failed: " #condition " should be false"); \
        } \
    } while(0)

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            std::ostringstream oss; \
            oss << "Assertion failed: expected " << (expected) << " but got " << (actual); \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)

#define ASSERT_NE(expected, actual) \
    do { \
        if ((expected) == (actual)) { \
            std::ostringstream oss; \
            oss << "Assertion failed: " << (expected) << " should not equal " << (actual); \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)

#define ASSERT_NULL(ptr) \
    do { \
        if ((ptr) != nullptr) { \
            throw std::runtime_error("Assertion failed: pointer should be null"); \
        } \
    } while(0)

#define ASSERT_NOT_NULL(ptr) \
    do { \
        if ((ptr) == nullptr) { \
            throw std::runtime_error("Assertion failed: pointer should not be null"); \
        } \
    } while(0)

#define ASSERT_THROWS(expression, exception_type) \
    do { \
        bool threw = false; \
        try { \
            expression; \
        } catch (const exception_type&) { \
            threw = true; \
        } catch (...) { \
            throw std::runtime_error("Assertion failed: threw wrong exception type"); \
        } \
        if (!threw) { \
            throw std::runtime_error("Assertion failed: expected exception " #exception_type " was not thrown"); \
        } \
    } while(0)

// 测试注册宏
#define TEST(test_name) \
    bool test_##test_name(); \
    struct TestRegistrar_##test_name { \
        TestRegistrar_##test_name() { \
            TestFramework::GetInstance().AddTest(#test_name, test_##test_name); \
        } \
    }; \
    static TestRegistrar_##test_name registrar_##test_name; \
    bool test_##test_name()

#endif // __TEST_FRAMEWORK_H__