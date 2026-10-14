// =============================================================================
// 堆排序 —— 空文件手写练习
// =============================================================================
//
// 【和 ds/tree/heap.cpp 的区别】
//   heap.cpp 里你写的是「最小堆：上浮/下沉 + push/pop」。
//   这里是「原地堆排序」——不开额外空间，直接在原数组上排完。
//
// 【面试会问的】
//   1. 建堆的复杂度是 O(n) 还是 O(n log n)？为什么？
//   2. 堆排序的复杂度？空间？稳定吗？
//   3. 堆排序和快排都是 O(n log n)，为什么堆排实际更慢？
//   4. 为什么排序要用「最大堆」而不是最小堆？
//   5. TopK 问题为什么用小顶堆？（和这里的方向相反，别搞混）
//
// 【编译运行】
//   cmake --build build --config Debug --target ds_sort_heap_sort
// =============================================================================

#include "test_util.h"
#include <random>

// -----------------------------------------------------------------------------
// TODO 1：下沉（sift down）
//
//   前提：arr[i] 的左右子树都已经满足「大顶堆」性质，
//         只有 arr[i] 自己可能比孩子小。
//   做法：把 arr[i] 和「较大的那个孩子」交换，然后递归/循环往下走。
//
//   ★ 注意是「较大的孩子」——这是和最小堆唯一的方向差别。
// -----------------------------------------------------------------------------
void sift_down(std::vector<int>& arr, int n, int i) {
    // TODO: 在这里实现
    //   提示：左孩子 = 2*i+1，右孩子 = 2*i+2（下标从 0 开始）
    (void)arr; (void)n; (void)i;
}

// -----------------------------------------------------------------------------
// TODO 2：建大顶堆
//
//   从「最后一个非叶子节点」开始往前依次下沉。
//   最后一个非叶子节点的下标 = n/2 - 1
//
//   ★ 面试点：为什么是 O(n) 而不是 O(n log n)？
//     因为大多数节点都在底层，底层节点下沉次数少。
//     严格证明：Σ(h 层的节点数 × 最多下沉 h 次) = O(n)
// -----------------------------------------------------------------------------
void build_max_heap(std::vector<int>& arr, int n) {
    // TODO: 在这里实现
    (void)arr; (void)n;
}

// -----------------------------------------------------------------------------
// TODO 3：原地堆排序
//
//   两步：
//     ① build_max_heap —— 先把数组变成大顶堆（此时 arr[0] 是最大值）
//     ② 循环：把 arr[0]（当前最大值）换到末尾，堆大小减 1，
//             对新堆顶做一次 sift_down
//
//   画一下：数组左边是「堆」，右边是「已排好的部分」，两边往中间缩。
// -----------------------------------------------------------------------------
void heap_sort(std::vector<int>& arr) {
    // TODO: 在这里实现
    (void)arr;
}

// =============================================================================
// 测试（已写好，不用改）
// =============================================================================
int main() {
    using namespace tst;
    std::cout << "===== 堆排序 测试 =====\n";

    // --- 基础正确性 ---
    {
        std::vector<int> a{5, 2, 9, 1, 5, 6};
        heap_sort(a);
        check_arr("普通输入 {5,2,9,1,5,6}", a, {1, 2, 5, 5, 6, 9});
    }
    {
        std::vector<int> a;
        heap_sort(a);
        check_arr("空数组", a, {});
    }
    {
        std::vector<int> a{42};
        heap_sort(a);
        check_arr("单元素", a, {42});
    }
    {
        std::vector<int> a{2, 1};
        heap_sort(a);
        check_arr("两个元素（逆序）", a, {1, 2});
    }
    {
        std::vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};
        heap_sort(a);
        check_arr("已经有序", a, {1, 2, 3, 4, 5, 6, 7, 8});
    }
    {
        std::vector<int> a{8, 7, 6, 5, 4, 3, 2, 1};
        heap_sort(a);
        check_arr("完全逆序", a, {1, 2, 3, 4, 5, 6, 7, 8});
    }
    {
        std::vector<int> a{7, 7, 7, 7, 7};
        heap_sort(a);
        check_arr("全部相同", a, {7, 7, 7, 7, 7});
    }
    {
        std::vector<int> a{-3, 0, -1, 2, -3, 5};
        heap_sort(a);
        check_arr("含负数", a, {-3, -3, -1, 0, 2, 5});
    }

    // --- 单独验证 sift_down（用「只有一个位置违反堆性质」的数组）---
    {
        // {1, 9, 8, 7, 6} —— 根节点 1 比孩子小，下沉后应该变成大顶堆
        std::vector<int> a{1, 9, 8, 7, 6};
        sift_down(a, (int)a.size(), 0);
        // 合法的大顶堆：每个节点 >= 它的孩子
        bool ok = true;
        for (int i = 0; i < (int)a.size(); i++) {
            int l = 2 * i + 1, r = 2 * i + 2;
            if (l < (int)a.size() && a[i] < a[l]) ok = false;
            if (r < (int)a.size() && a[i] < a[r]) ok = false;
        }
        check_true("sift_down 后满足大顶堆性质", ok);
    }

    // --- 验证 build_max_heap ---
    {
        std::vector<int> a{3, 1, 4, 1, 5, 9, 2, 6};
        build_max_heap(a, (int)a.size());
        bool ok = true;
        for (int i = 0; i < (int)a.size(); i++) {
            int l = 2 * i + 1, r = 2 * i + 2;
            if (l < (int)a.size() && a[i] < a[l]) ok = false;
            if (r < (int)a.size() && a[i] < a[r]) ok = false;
        }
        check_true("build_max_heap 后满足大顶堆性质", ok);
        check("堆顶是最大值", a.empty() ? -1 : a[0], 9);
    }

    // --- 性能对比：堆排 vs std::sort ---
    {
        std::mt19937 rng(7);
        std::uniform_int_distribution<int> dist(-100000, 100000);
        std::vector<int> a(50000), b;
        for (int& x : a) x = dist(rng);
        b = a;

        double ms1 = time_ms([&] { heap_sort(a); });
        double ms2 = time_ms([&] { std::sort(b.begin(), b.end()); });
        std::cout << "  随机 5 万个数: 堆排 = " << ms1
                  << " ms,  std::sort = " << ms2 << " ms\n";
        std::cout << "  ↑ 同样是 O(n log n)，为什么慢？（提示：cache 局部性）\n";
        check_arr("随机 5 万个数排序正确", a, b);
    }

    return summary("堆排序");
}
