# 数据结构与算法手写实现（C / C++）

> 计算机科学与技术 · 大二在读
> 手写实现常用数据结构与算法，配套 LeetCode 刷题。

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

---

## 环境

- **语言**：C++20 / C11
- **编译器**：MSVC 14.44（Visual Studio 2022）
- **构建**：CMake ≥ 3.16

---

## 构建

**每个 `.cpp` 会被编译成一个独立的可执行文件**，互不冲突。

```bash
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

产物在 `build/bin/Debug/`（共 16 个可执行文件）：

```
ds_graph_A_star.exe          ds_hash_hash.exe             ds_tree_heap.exe
ds_graph_graph.exe           ds_linear_bfs.exe            ds_tree_bst_traversal.exe
ds_graph_GraphMatrix.exe     ds_linear_stack_expr.exe     ds_linear_undo_redo.exe
...
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
│  └─ graph/               # 图
├─ ch09/ ch10/             # C 语言章节练习
└─ bilibili指针/            # 指针专题练习
```

---

## 设计要点

**哈希表**（`ds/hash/hash.cpp`）
- 拉链法解决冲突；`capacity` / `size` 双计数
- 负载因子超阈值时 rehash（复用节点、只重算桶下标）
- 显式 `= delete` 拷贝构造/赋值 —— 默认浅拷贝会导致桶数组双重释放

**图**（`ds/graph/`）
- 三种表示各写一遍，用来对比空间/时间取舍：
  邻接表（链表版）、邻接表（vector 版）、邻接矩阵
- BFS 用队列（求无权图最短路），DFS 用显式栈（防栈溢出）
- A\* 用 `priority_queue<Node, vector<Node>, greater<Node>>`，
  采用**惰性删除**（取出时判 `cur.g > gScore[...]` 就直接跳过），
  避免维护 `decrease-key` 所需的索引结构

**堆**（`ds/tree/heap.cpp`）
- 上浮 / 下沉手写；支持 TopK 与原地堆排序

**撤销恢复**（`ds/linear/undo_redo.cpp`）
- 双栈（undo / redo），新操作时清空 redo 栈

---

## 开发约定

- **源文件编码统一 UTF-8（无 BOM）**，编译器开 `/utf-8`
- **警告全开**：MSVC `/W4 /permissive- /Zc:__cplusplus`，GCC `-Wall -Wextra -Wshadow -Wnon-virtual-dtor`
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
- [ ] 单元测试（Catch2）

---

## License

MIT
