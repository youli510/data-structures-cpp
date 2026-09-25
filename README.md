# 数据结构与算法手写实现（C / C++）

> 计算机科学与技术 · 大二在读
> 手写实现常用数据结构与算法，配套 LeetCode 刷题与项目实践。
> 目标岗位：**游戏客户端 / 游戏服务端开发**

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-%E2%89%A53.16-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](LICENSE)

---

## 内容

| 目录 | 内容 | 状态 |
|---|---|---|
| [`Project1/ds/linear/`](Project1/ds/linear) | 数组栈 / 链表栈 / 循环队列 / 顺序队列 / 链表队列 / 消息队列 / 表达式求值 / 撤销恢复 / 快慢指针应用 | ✅ |
| [`Project1/ds/hash/`](Project1/ds/hash) | 哈希表：拉链法 + 容量元素双计数 + rehash + 禁用拷贝 | ✅ |
| [`Project1/ds/tree/`](Project1/ds/tree) | 二叉树前中后序遍历（递归 6 种 + 迭代 6 种）、层序遍历、最小堆（上浮/下沉） | ✅ |
| [`Project1/ds/graph/`](Project1/ds/graph) | 图的三种表示（邻接表链表 / 邻接表 vector / 邻接矩阵）+ BFS / DFS / A\* | ✅ |
| [`Project1/ch09/`](Project1/ch09) · [`ch10/`](Project1/ch10) | C 语言指针与数组章节练习 | ✅ |
| [`Project1/ProjectLab/`](Project1/ProjectLab) | 开源项目源码分析、学习路线、八股映射、工具脚本 | 🚧 |

**当前进度**见 [`Project1/ds/CONTEXT.md`](Project1/ds/CONTEXT.md)，刷题清单见 `Project1/ds/LeetCode_Roadmap.docx`。

---

## 环境

- **语言**：C++20 / C11
- **编译器**：MSVC 14.44（Visual Studio 2022）
- **构建**：CMake ≥ 3.16
- **Python 3.6+**（仅 `ProjectLab/scripts/` 下的工具脚本需要）

---

## 构建

**每个 `.cpp` 会被编译成一个独立的可执行文件**，互不冲突。

```bash
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

产物在 `build/bin/Debug/`：

```
ds_graph_A_star.exe          ds_hash_hash.exe             ds_tree_heap.exe
ds_graph_graph.exe           ds_linear_bfs.exe            ds_tree_bst_traversal.exe
ds_graph_GraphMatrix.exe     ds_linear_stack_expr.exe     ds_linear_undo_redo.exe
...                          共 16 个可执行文件
```

**只编译一个**：
```bash
cmake --build build --config Debug --target ds_hash_hash
```

### 关于「没有 main() 的文件」

`circ_queue.cpp` / `queue_linked.cpp` / `seq_queue.cpp` / `stack_linked.cpp`
是**数据结构实现**（设计上作为零件被其他程序使用），本身没有 `main()`。
`CMakeLists.txt` 会自动识别并把它们编译成 **OBJECT 库** ——
**照样做语法检查**，但不会因为缺 `main` 而链接失败。

---

## 目录结构

```
Project1/
├─ CMakeLists.txt          # 每个 .cpp 一个可执行文件
├─ ds/
│  ├─ CONTEXT.md           # 学习进度
│  ├─ linear/              # 线性结构
│  ├─ hash/                # 哈希表
│  ├─ tree/                # 树与堆
│  ├─ graph/               # 图
│  └─ ProjectLab/          # 项目分析库（见下）
├─ ch09/ ch10/             # C 语言章节练习
└─ bilibili指针/            # 指针专题练习
```

---

## ProjectLab —— 开源项目源码分析库

`Project1/ProjectLab/` 是我对 5 个真实开源项目的**源码级分析**（含架构、算法、缺陷诊断、面试映射）：

| 项目 | 一句话 | 我分析出的重点 |
|---|---|---|
| [marukrap/ProceduralMapGenerator](https://github.com/marukrap/ProceduralMapGenerator) | C++17 地牢生成算法大全 | 模板方法 + 多态容器；洪水填充（= LC200）；**Prim 从 O(V³) 优化到 O(V²)** |
| [yujqiao/DungeonRush](https://github.com/yujqiao/DungeonRush) | 纯 C + SDL2 完整肉鸽 | 主循环 6 步；**前瞻启发式 AI**；帧同步；18 个缺陷诊断 |
| [mayerui/sudoku](https://github.com/mayerui/sudoku) | 工程规范教科书 | 三层 CMake + 三平台 CI；`CBlock` 视图模式；**位掩码把 O(n²) 降到 O(n)** |
| [taylorconor/tinytetris](https://github.com/taylorconor/tinytetris) | 2077 字节的俄罗斯方块 | 一个 `int` 装 10 个 2 位字段；**找到 4 个疑似 bug** |
| [ssloy/tinyrenderer](https://github.com/ssloy/tinyrenderer) | 500 行软渲染器 | 重心坐标光栅化；**透视校正插值**；shadow acne |

还有 `ProjectLab/scripts/` 里的工具（可直接运行）：

| 脚本 | 用途 |
|---|---|
| `check_env.ps1` | 一键体检：工具链 + 仓库健康 + 编码 + 已知代码问题 |
| `fix_encoding.py` | 源文件 GBK → UTF-8 批量转换（自动备份、默认 dry-run） |
| `CMakeLists-root.txt` | 上面那个「每 cpp 一个 exe」的构建脚本 |
| `gitignore-template.txt` | VS 项目的 `.gitignore` 完整版 |

---

## 开发约定

- **源文件编码统一 UTF-8（无 BOM）**，编译器开 `/utf-8`。详见 [`ProjectLab/05-编码规范（UTF-8）.md`](Project1/ProjectLab/05-编码规范（UTF-8）.md)
- **警告全开**：MSVC `/W4 /permissive- /Zc:__cplusplus`，GCC `-Wall -Wextra -Wshadow -Wnon-virtual-dtor`
- 提交前跑一次编码自检：
  ```bash
  python Project1/ProjectLab/scripts/fix_encoding.py Project1 --dry-run
  ```
- Commit message 用 Conventional Commits：`feat:` / `fix:` / `refactor:` / `docs:` / `test:` / `chore:`

---

## 已完成 / 计划

- [x] 栈、队列、链表、哈希表、树、堆、图 手写实现
- [x] 三种图的表示 + BFS / DFS / A\*
- [x] CMake 工程化（每个 cpp 独立可执行）
- [x] 源文件编码统一 UTF-8
- [ ] 排序（快排 / 归并 / 堆排 手写）+ 二分查找
- [ ] C++ 深入（智能指针 / 移动语义 / 虚函数表 / RAII / STL 源码）
- [ ] LeetCode 50 题
- [ ] 肉鸽（Roguelike）小游戏 —— 结合地牢生成 + A\* 寻路 + 道具系统
- [ ] 单元测试（Catch2）

---

## License

MIT
