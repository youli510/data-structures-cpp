# 当前学习状态

## 进度
- [x] 栈（3种实现 + 括号匹配 + 撤销/重做 + 函数调用栈）
- [x] 队列（3种实现 + BFS + 消息队列）
- [x] 哈希表（拉链法 + rehash）
- [x] 树（前中后序，递归6种+迭代6种，层序BFS）
- [x] 堆（最小堆/最大堆 + 上浮/下沉 + TopK + 堆排序 + 原地堆排序）
- [x] 图（邻接表链表版 + vector版 + 邻接矩阵；BFS/DFS递归/迭代；A* 寻路；LeetCode 200 AC）
- [x] 排序（快排：Lomuto/随机pivot/三路；归并：数组+链表；堆排：sift_down/建堆/原地）三项全通过
- [x] 二分查找（binary_search / lower_bound / upper_bound / 旋转数组 / 找峰值）22 项通过

## 下一步
1. LeetCode 刷题（二分答案 LC875 / 1011 / 410）
2. C++ 深入（智能指针/移动语义/虚函数表/STL 源码）
3. 图形学（Games101）→ 引擎（Unity/UE）

## 关键文件
- ds/linear/ → 栈/队列/链表
- ds/hash/ → 哈希表
- ds/tree/ → 树遍历 + 堆
- ds/graph/ → 图（含 A*）
- ds/sort/quick_sort.cpp → 快排（Lomuto/随机pivot/三路）✅ 11项通过
- ds/sort/merge_sort.cpp → 归并（数组+链表）✅ 11项通过
- ds/sort/heap_sort.cpp → 堆排（sift_down/build_max_heap/heap_sort）✅ 12项通过
- ds/sort/Sorting_Study_Notes.docx → 排序笔记（三种算法 + 实测数据 + 踩坑 + 面试题）
- ds/binary_search/binary_search.cpp → 5 个二分函数 ✅ 22项通过
- ds/binary_search/BinarySearch_Study_Notes.docx → 二分笔记（三个模板 + 单调谓词 + 踩坑）
- ds/LeetCode_Roadmap.docx → 刷题清单

## 最近更新
2026-10-18 排序：快排（4 个 TODO）+ 归并（3 个 TODO）全部通过；下一步堆排

## 最近更新
2026-10-18 排序三件套 + 二分查找全部完成；生成排序/二分笔记

## 遗留事项
- heap_sort.cpp 第 74 行 `int n = arr.size()` 可改成 `(int)arr.size()` 消 C4267 警告
- 构建命令（cmake 不在 PATH，VS 自带）：
  S:\vs\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe --build build --config Debug --target <名>

## 笔记体系（都在各目录下）
- ds/linear/LinkedList_Stack_Notes.docx
- ds/hash/HashTable_Study_Notes.docx
- ds/tree/Tree_Study_Notes.docx + Heap_Study_Notes.docx
- ds/sort/Sorting_Study_Notes.docx
- ds/binary_search/BinarySearch_Study_Notes.docx
- ds/LeetCode_Roadmap.docx