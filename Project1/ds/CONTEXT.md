# 当前学习状态

## 进度
- [x] 栈（3种实现 + 括号匹配 + 撤销/重做 + 函数调用栈）
- [x] 队列（3种实现 + BFS + 消息队列）
- [x] 哈希表（拉链法 + rehash）
- [x] 树（前中后序，递归6种+迭代6种，层序BFS）
- [x] 堆（最小堆/最大堆 + 上浮/下沉 + TopK + 堆排序 + 原地堆排序）
- [x] 图（邻接表链表版 + vector版 + 邻接矩阵；BFS/DFS递归/迭代；A* 寻路；LeetCode 200 AC）
- [ ] 排序 ← 当前（快排 ✅ / 归并 ✅ / 堆排 待做）
## 下一步
1. 堆排（heap_sort.cpp，当前 4 通过 / 8 失败）
2. 二分查找
3. C++ 深入（智能指针/移动语义/虚函数表）

## 关键文件
- ds/linear/ → 栈/队列/链表
- ds/hash/ → 哈希表
- ds/tree/ → 树遍历 + 堆
- ds/graph/ → 图（含 A*）
- ds/sort/quick_sort.cpp → 快排（Lomuto/随机pivot/三路）✅ 11项通过
- ds/sort/merge_sort.cpp → 归并（数组+链表）✅ 11项通过
- ds/sort/heap_sort.cpp → 堆排（待做）
- ds/LeetCode_Roadmap.docx → 刷题清单

## 最近更新
2026-10-18 排序：快排（4 个 TODO）+ 归并（3 个 TODO）全部通过；下一步堆排

## 待办
- heap_sort.cpp：4 通过 / 8 失败，还没开始
- 之后：二分查找、C++ 深入
- 构建命令（cmake 不在 PATH，VS 自带）：
  S:\vs\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe --build build --config Debug --target <名>