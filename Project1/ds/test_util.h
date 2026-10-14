#ifndef DS_TEST_UTIL_H
#define DS_TEST_UTIL_H
// =============================================================================
// test_util.h —— 所有练习共用的测试辅助
//
// 为什么放在 ds/ 而不是 ds/sort/？
//   因为 ds/sort/ 和 ds/binary_search/ 都要用它。
//   CMakeLists.txt 里已经把 ds/ 加进了头文件搜索路径，所以
//   在任何子目录写 #include "test_util.h" 都能找到。
//
// ★ 顺带学两个知识点：
//   1. 头文件用 #ifndef / #define / #endif 做「包含保护」，
//      防止同一个 .h 被 include 两次导致重复定义。
//      （现代 C++ 也可以写 #pragma once，更短）
//   2. CMake 的 target_include_directories(... PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ds)
//      就是把 ds/ 目录「告诉编译器：找头文件时也来这里看看」。
// =============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

namespace tst {

inline int g_pass = 0;
inline int g_fail = 0;

// ---- 断言：整数相等 ----
inline void check(const std::string& name, long long got, long long want) {
    if (got == want) {
        std::cout << "  [ OK ] " << name << " = " << got << "\n";
        ++g_pass;
    } else {
        std::cout << "  [FAIL] " << name << " = " << got << "   期望 " << want << "\n";
        ++g_fail;
    }
}

// ---- 断言：数组相等 ----
inline void check_arr(const std::string& name,
                      const std::vector<int>& got,
                      const std::vector<int>& want) {
    if (got == want) {
        std::cout << "  [ OK ] " << name << "\n";
        ++g_pass;
    } else {
        std::cout << "  [FAIL] " << name << "\n";
        std::cout << "         得到: ";
        for (int x : got)  std::cout << x << ' ';
        std::cout << "\n         期望: ";
        for (int x : want) std::cout << x << ' ';
        std::cout << "\n";
        ++g_fail;
    }
}

// ---- 断言：布尔 ----
inline void check_true(const std::string& name, bool cond) {
    if (cond) { std::cout << "  [ OK ] " << name << "\n"; ++g_pass; }
    else      { std::cout << "  [FAIL] " << name << "\n";  ++g_fail; }
}

// ---- 计时（返回毫秒）----
template <typename F>
inline double time_ms(F&& f) {
    auto t0 = std::chrono::high_resolution_clock::now();
    f();
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

// ---- 收尾：打印统计，返回退出码 ----
inline int summary(const char* who) {
    std::cout << "\n----------------------------------------\n";
    if (g_fail == 0)
        std::cout << who << ": 全部通过（" << g_pass << " 项）\n";
    else
        std::cout << who << ": " << g_pass << " 通过 / " << g_fail << " 失败\n";
    std::cout << "----------------------------------------\n";
    return g_fail == 0 ? 0 : 1;
}

} // namespace tst

#endif // DS_TEST_UTIL_H
