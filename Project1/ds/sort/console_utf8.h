// =============================================================================
// console_utf8.h —— 让 Windows 控制台正确显示 UTF-8 中文
// =============================================================================
//
// 【为什么需要这个文件】
//
//   本项目的编译选项里有 /utf-8，它同时设置了：
//     /source-charset:utf-8      → 源码文件按 UTF-8 读
//     /execution-charset:utf-8   → 字符串字面量在 exe 里存成 UTF-8 字节
//
//   但 Windows 控制台（cmd / VS 调试台）的默认代码页是 936（GBK）。
//   于是 std::cout << "按关键字排序"; 输出的 UTF-8 字节被控制台按 GBK 解码，
//   显示成「鎸夊叧閿瓧鎺掑簭」这种乱码。
//
//   解决办法：程序一启动就把控制台切成 UTF-8（代码页 65001）。
//
// 【怎么让它对所有 exe 生效】
//
//   不在每个 .cpp 里写 #include —— 那样 24 个文件都要改。
//   CMakeLists.txt 里用 MSVC 的 /FI（Forced Include，强制包含）参数：
//
//       add_compile_options("/FI${CMAKE_CURRENT_SOURCE_DIR}/ds/console_utf8.h")
//
//   CMake 会把它翻译成 .vcxproj 里的 <ForcedIncludeFiles> 节点。
//   于是编译器编译【每一个】.cpp 时都会自动在最前面插入本头文件，
//   下面的全局对象在 main() 之前完成构造 → 控制台已是 UTF-8。
//
// =============================================================================
// 【★ 踩坑记录：为什么这里不 #include <windows.h> ★】
// =============================================================================
//
//   第一版写的是 #include <windows.h>，结果整个项目 **190 个编译错误**，
//   全部集中在 ds/linear/undo_redo.cpp 一个文件里：
//
//       undo_redo.cpp(9,23): error C2143: 语法错误: 缺少"}"(在"("的前面)
//       undo_redo.cpp(9,23): error C2059: 语法错误:"常数"
//       undo_redo.cpp(13,13): error C2065: "action": 未声明的标识符
//       undo_redo.cpp(13,7): error C2923: "std::stack": "action" 不是有效的模板参数
//
//   而那一行长这样：
//
//       enum Type { INSERT, DELETE } type;     // ← 第 8 行
//
//   原因：<windows.h>（实际上是 winnt.h）里有
//
//       #define DELETE  0x00010000            // 删除文件的访问权限
//
//   于是枚举值 DELETE 被预处理器替换成 0x00010000：
//
//       enum Type { INSERT, 0x00010000 } type;   // ← 语法炸了
//
//   接着 action 结构体定义失败 → std::stack<action> 连锁报错。
//
//   ★ 教训：<windows.h> 是一颗「宏地雷阵」，常见地雷（都是 #define）：
//
//       DELETE  IN  OUT  ERROR  small  near  far  min  max  interface
//       GetMessage  CreateFile  DrawText  LoadImage  PlaySound  Yield
//       RemoveProp  SendMessage  SetWindowLong  UpdateWindow  Status ...
//
//   平时 #include <windows.h> 只出现在个别文件里，踩雷是偶发；
//   但 /FI 是把它塞进【每一个 .cpp】——任何一处踩雷，全项目编译失败。
//
//   ★ 所以这里改成「只声明需要的那两个函数」：
//       零宏污染、零副作用、不引入任何 windows 头文件。
//     声明和 Windows SDK 里的原型完全一致，链接时由 kernel32.lib 解析。
//
// =============================================================================

#pragma once

#if defined(_WIN32)

// ---------------------------------------------------------------------------
// 声明（不是包含！）kernel32.dll 里的两个控制台代码页函数
// ---------------------------------------------------------------------------
//   Windows SDK 里的原型：
//     WINBASEAPI BOOL WINAPI SetConsoleOutputCP(_In_ UINT wCodePageID);
//     WINBASEAPI BOOL WINAPI SetConsoleCP(_In_ UINT wCodePageID);
//   展开后： BOOL = int, WINAPI = __stdcall, UINT = unsigned int
//
//   __declspec(dllimport) 表示「这个函数在 DLL 里」，
//   由默认链接的 kernel32.lib 提供导入信息。
// ---------------------------------------------------------------------------

#  if defined(_MSC_VER)
#    define DS_CONSOLE_DECL __declspec(dllimport)
#  else
#    define DS_CONSOLE_DECL          // MinGW / Clang 用默认链接即可
#  endif

extern "C" {

DS_CONSOLE_DECL int __stdcall SetConsoleOutputCP(unsigned int codePage);
DS_CONSOLE_DECL int __stdcall SetConsoleCP(unsigned int codePage);

}  // extern "C"

#  undef DS_CONSOLE_DECL

// ---------------------------------------------------------------------------
// 全局对象：main() 之前构造 → 控制台代码页已切成 UTF-8
// ---------------------------------------------------------------------------
namespace ds_detail {

struct ConsoleUtf8Init {
    ConsoleUtf8Init() noexcept {
        constexpr unsigned int kUtf8CodePage = 65001u;   // 65001 = UTF-8
        ::SetConsoleOutputCP(kUtf8CodePage);   // 影响 std::cout 的中文输出
        ::SetConsoleCP(kUtf8CodePage);         // 影响 std::cin  的中文输入
    }
};

// C++17 的 inline 变量：即使在多个 .cpp 里都包含本头文件，
// 整个程序也只有一个实例，不会重复定义。
inline ConsoleUtf8Init g_console_utf8_init;

}  // namespace ds_detail

#endif  // _WIN32
