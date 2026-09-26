# =============================================================================
# 本仓库根目录的 CMakeLists.txt
#
# 目的：一个仓库里放 N 个「各自带 main()」的学习用 cpp，
#       每个 .cpp 编成一个独立的可执行文件，互不冲突。
#       （解决原 .vcxproj 只能编一个 main 的问题）
#
# 用法：
#   cmake -B build -G "Visual Studio 17 2022" -A x64
#   cmake --build build --config Debug
#   产物：build\bin\Debug\<每个cpp一个exe>
#
#   或者用 Ninja（更快，需要装 ninja）：
#   cmake -B build -G Ninja
#   cmake --build build
# =============================================================================

cmake_minimum_required(VERSION 3.16)

project(Project1_DS_Lab LANGUAGES C CXX)

# -----------------------------------------------------------------------------
# 语言标准
# -----------------------------------------------------------------------------
set(CMAKE_C_STANDARD   11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)      # 用 -std=c++20 而不是 -std=gnu++20

# -----------------------------------------------------------------------------
# ★ 编译选项：警告拉满 + 强制 UTF-8（解决中文注释乱码）
# -----------------------------------------------------------------------------
if (MSVC)
    # /W4      : 4 级警告（默认是 /W3）
    # /utf-8   : 源码和执行字符集都用 UTF-8  ← ★ 关键！
    # /permissive- : 更严格的标准一致性
    # /Zc:__cplusplus : 让 __cplusplus 宏正确反映 C++ 标准
    add_compile_options(/W4 /utf-8 /permissive- /Zc:__cplusplus)

    # /wd4996 : 屏蔽「strcpy 不安全」这类 CRT 安全警告（学习项目里噪音太多）
    # 如果想让它们显示出来，注释掉下一行
    add_compile_options(/wd4996)

    # 静态分析（可选，会慢很多；需要时手动打开）
    # add_compile_options(/analyze)

    # ★★★ 优化选项必须用「生成器表达式」，不能用 if(CMAKE_BUILD_TYPE ...) ★★★
    #
    # 为什么？—— 这是我实测踩到的坑：
    #   Visual Studio 是「多配置生成器（multi-config generator）」。
    #   在 configure 阶段，CMAKE_BUILD_TYPE 是【空字符串】，既不是 "Debug" 也不是 "Release"！
    #   所以 if(CMAKE_BUILD_TYPE STREQUAL "Debug") 恒为 FALSE，
    #   会走 else 分支加上 /O2；然后 cmake --build --config Debug 时
    #   MSBuild 又会加上它自己的 Debug 默认 /RTC1
    #   → 报错：error D8016: "/O2"和"/RTC1"命令行选项不兼容
    #
    # 正确做法：用 $<CONFIG:...> 生成器表达式，它在【构建时】按实际配置求值。
    add_compile_options(
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Debug>:/RTC1>
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:RelWithDebInfo>:/O2>
        $<$<CONFIG:MinSizeRel>:/O1>
    )

    # 运行时库保持默认（Debug 用 /MDd，Release 用 /MD），不用手动设置
    #
    # 备选（更省事）：MSVC 的默认优化选项其实已经对了
    #   Debug   = /Od /RTC1
    #   Release = /O2
    #   所以上面这段可以整块删掉。我保留它只是为了显式表达意图。

else()
    # GCC / Clang
    add_compile_options(
        -Wall               # 常用警告
        -Wextra             # 更多警告
        -Wshadow            # ★ 变量遮蔽（D2 项目里那个 bug 就靠它抓）
        -Wconversion        # 隐式窄化转换（学习项目可能噪音较多，可关）
        -Wsign-conversion
        -Wnon-virtual-dtor  # ★ 基类有虚函数但析构非虚（D3 的 KeyMap bug 靠它抓）
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -finput-charset=utf-8    # ★ 源码字符集
        -fexec-charset=utf-8     # ★ 执行字符集
    )

    # GCC/Clang 用 Makefile/Ninja 时是「单配置生成器」，CMAKE_BUILD_TYPE 是可用的；
    # 但为了和 MSVC 分支一致、并且兼容 Ninja Multi-Config，这里也用生成器表达式。
    add_compile_options(
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-g3>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:Release>:-g>
    )

    # 链接期优化（Release）—— 同样用生成器表达式
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_OK OUTPUT IPO_MSG)
    if (IPO_OK)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO ON)
    endif()
endif()

# -----------------------------------------------------------------------------
# 输出目录
# -----------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY        ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY        ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY        ${CMAKE_BINARY_DIR}/lib)

# 多配置生成器（VS / Xcode）会加子目录 Debug/Release，统一一下
foreach(cfg IN ITEMS DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/bin/${cfg})
endforeach()

# -----------------------------------------------------------------------------
# ★ 核心：每个 .cpp 编成一个独立的可执行文件
# -----------------------------------------------------------------------------
# 扫描哪些目录（按需增删）
set(SCAN_DIRS
    ds/linear
    ds/hash
    ds/tree
    ds/graph
    ds
    ch09
    ch10
    "bilibili指针"
)

# 收集所有 .cpp（CONFIGURE_DEPENDS = 新增文件后自动重新配置）
set(ALL_SOURCES "")
foreach(d ${SCAN_DIRS})
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${d}")
        file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
             "${CMAKE_CURRENT_SOURCE_DIR}/${d}/*.cpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/${d}/*.cc"
             "${CMAKE_CURRENT_SOURCE_DIR}/${d}/*.cxx")
        list(APPEND ALL_SOURCES ${SRC})
    endif()
endforeach()

list(REMOVE_DUPLICATES ALL_SOURCES)
list(SORT ALL_SOURCES)

# 显式排除的文件（例如暂时编不过的）
set(EXCLUDE_SOURCES
    # "${CMAKE_CURRENT_SOURCE_DIR}/ds/xxx/yyy.cpp"
)

# -----------------------------------------------------------------------------
# ★ 自动跳过「没有 main()」的文件
#   为什么需要？
#     实测发现 ds/linear 下有 3 个文件（queue_linked.cpp / stack_linked.cpp /
#     seq_queue.cpp）是「零件文件」——它们是数据结构实现，设计上要被别的
#     测试程序 include，本身没有 main()。
#     如果给它们建 add_executable，会报：
#       error LNK2019: 无法解析的外部符号 main
#     所以这里读一下文件内容，没有 main 的就不建 target。
# -----------------------------------------------------------------------------
set(CREATED_TARGETS "")
set(SKIPPED_NO_MAIN "")
set(FAILED_TO_READ "")

foreach(src ${ALL_SOURCES})
    # 1) 显式排除
    list(FIND EXCLUDE_SOURCES "${src}" _idx)
    if (NOT _idx EQUAL -1)
        continue()
    endif()

    # 2) 检查有没有 main()
    if (NOT EXISTS "${src}")
        list(APPEND FAILED_TO_READ "${src}")
        continue()
    endif()
    file(READ "${src}" _src_content)
    # 匹配 int main( / int main ( / int main(void) 等
    set(_has_main FALSE)
    if (_src_content MATCHES "int[ \t\r\n]+main[ \t\r\n]*\\(")
        set(_has_main TRUE)
    endif()

    # ★★★ target 名必须在这里算好 ★★★
    #   （踩过的坑：一开始把这段放在 add_library(${tname}_obj ...) 之后，
    #     result：tname 在计算前就被使用 → OBJECT 库会沿用【上一个文件】的名字，
    #     表现为 "ds_linear_seq_list_obj.vcxproj 在编译 seq_queue.cpp" 这种错乱。）
    file(RELATIVE_PATH rel "${CMAKE_CURRENT_SOURCE_DIR}" "${src}")
    string(REPLACE "/" "_" tname "${rel}")
    string(REPLACE "\\" "_" tname "${tname}")
    string(REGEX REPLACE "\\.(cpp|cc|cxx|c)$" "" tname "${tname}")
    # 去掉可能的非 ASCII（VS 生成器对目标名里的中文不太友好）
    string(REGEX REPLACE "[^A-Za-z0-9_]" "_" tname "${tname}")
    # 去重（防御性）
    list(FIND CREATED_TARGETS "${tname}" _dup)
    if (NOT _dup EQUAL -1)
        set(tname "${tname}_2")
    endif()
    list(APPEND CREATED_TARGETS "${tname}")

    if (NOT _has_main)
        # ★ 没有 main() 的文件：仍然编译它（这样语法错误会被发现），
        #   但编译成 OBJECT 库而不是可执行文件（所以不会因为缺 main 而链接失败）。
        #   如果直接 continue() 跳过，那么这类文件里的 bug 又会藏起来。
        get_filename_component(_rel "${src}" NAME)
        list(APPEND SKIPPED_NO_MAIN "${_rel}")
        add_library(${tname}_obj OBJECT "${src}")
        target_include_directories(${tname}_obj PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/ds
            ${CMAKE_CURRENT_SOURCE_DIR}/ch09
            ${CMAKE_CURRENT_SOURCE_DIR}/ch10
        )
        if (MSVC)
            target_compile_options(${tname}_obj PRIVATE /utf-8)
        endif()
        set_target_properties(${tname}_obj PROPERTIES FOLDER "ds_lab_obj")
        continue()
    endif()

    add_executable(${tname} "${src}")

    # 头文件搜索路径（按需增删）
    target_include_directories(${tname} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/ds
        ${CMAKE_CURRENT_SOURCE_DIR}/ch09
        ${CMAKE_CURRENT_SOURCE_DIR}/ch10
    )

    # MSVC：让中文源文件（如果还有）更好处理；同时关闭「SDL 检查」
    if (MSVC)
        target_compile_options(${tname} PRIVATE /utf-8)
    endif()

    # 给 target 分组（VS 里显示成文件夹，而不是几百个平铺的工程）
    set_target_properties(${tname} PROPERTIES
        FOLDER "ds_lab"
    )
endforeach()

list(LENGTH CREATED_TARGETS N_TARGETS)

# -----------------------------------------------------------------------------
# 汇总信息
# -----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "=======================================================")
message(STATUS " Project1 DS Lab")
message(STATUS "=======================================================")
message(STATUS " 源码根目录 : ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS " 构建目录   : ${CMAKE_BINARY_DIR}")
message(STATUS " 输出目录   : ${CMAKE_BINARY_DIR}/bin")
message(STATUS " 编译器     : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS " C++ 标准   : ${CMAKE_CXX_STANDARD}")
message(STATUS " 生成目标数 : ${N_TARGETS}")
if (SKIPPED_NO_MAIN)
    list(LENGTH SKIPPED_NO_MAIN _n_skip)
        message(STATUS " 无main(编为OBJ): ${_n_skip} 个 -> ${SKIPPED_NO_MAIN}")
endif()
message(STATUS "-------------------------------------------------------")
message(STATUS " 用法:")
message(STATUS "   cmake --build build --config Debug")
message(STATUS "   .\\build\\bin\\Debug\\<target>.exe")
message(STATUS " 或者只编一个:")
message(STATUS "   cmake --build build --config Debug --target <name>")
message(STATUS "=======================================================")
message(STATUS "")

if (N_TARGETS EQUAL 0)
    message(WARNING "没有找到任何源文件！检查 SCAN_DIRS 是否写对了。")
endif()

# -----------------------------------------------------------------------------
# 可选：CTest（以后加测试用）
# -----------------------------------------------------------------------------
# include(CTest)
# if (BUILD_TESTING)
#     add_subdirectory(tests)
# endif()
