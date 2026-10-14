// =============================================================================
// 快速排序 —— 空文件手写练习
// =============================================================================
//
// 【要求】不看资料，把下面 4 个 TODO 写出来。
//         跑一遍：全 [ OK ] 就说明写对了；有 [FAIL] 就回去查。
//
// 【面试会问的（写完自己回答一遍）】
//   1. 平均 / 最坏时间复杂度？最坏出现在什么输入上？
//   2. 怎么把最坏情况从 O(n²) 降到期望 O(n log n)？
//   3. 快排稳定吗？为什么？
//   4. 快排和堆排都是 O(n log n)，为什么实际快排更快？
//   5. 三路快排在什么数据上优势明显？
//
// 【编译运行】
//   cmake --build build --config Debug --target ds_sort_quick_sort
//   .\build\bin\Debug\ds_sort_quick_sort.exe
// =============================================================================

#include "test_util.h"
#include <random>

// -----------------------------------------------------------------------------
// TODO 1：Lomuto 分区（最直观的写法）
//
//   思路：选 arr[hi] 作为 pivot，用 i 维护「小于等于 pivot 的区域」的右边界。
//         遍历 lo..hi-1，遇到 <= pivot 的就把它换到 i 位置并 i++。
//         最后把 pivot 换到 i 位置。
//
//   返回值：pivot 最终所在的下标
//   效果：  分区后 arr[lo..p-1] <= pivot，arr[p] == pivot，arr[p+1..hi] > pivot
// -----------------------------------------------------------------------------
int partition_lomuto(std::vector<int>& arr, int lo, int hi) {
    // TODO: 在这里实现
    (void)arr; (void)lo; (void)hi;
    return hi;   // 占位，让测试失败而不是崩溃
}

// -----------------------------------------------------------------------------
// TODO 2：用上面的 partition 写递归快排
//
//   注意递归出口（lo >= hi 时返回）
// -----------------------------------------------------------------------------
void quick_sort(std::vector<int>& arr, int lo, int hi) {
    // TODO: 在这里实现
    (void)arr; (void)lo; (void)hi;
}

// 对外接口（已写好，不用改）
void quick_sort(std::vector<int>& arr) {
    if (!arr.empty()) quick_sort(arr, 0, (int)arr.size() - 1);
}

// -----------------------------------------------------------------------------
// TODO 3：随机 pivot 版（避免「已经有序」这种输入退化成 O(n²)）
//
//   思路：在分区前，先把 arr[hi] 和一个随机位置的元素交换，
//         这样「已有序」的输入也不会每次都选到极值当 pivot。
//
//   ★ 面试点：为什么「固定选最后一个」在已排序数组上会退化成 O(n²)？
// -----------------------------------------------------------------------------
int partition_random(std::vector<int>& arr, int lo, int hi) {
    // TODO: 在这里实现（可以先随机交换 arr[hi]，再复用 partition_lomuto 的逻辑）
    (void)arr; (void)lo; (void)hi;
    return hi;
}

void quick_sort_random(std::vector<int>& arr, int lo, int hi) {
    // TODO: 在这里实现
    (void)arr; (void)lo; (void)hi;
}

void quick_sort_random(std::vector<int>& arr) {
    if (!arr.empty()) quick_sort_random(arr, 0, (int)arr.size() - 1);
}

// -----------------------------------------------------------------------------
// TODO 4：三路快排（Dutch National Flag，处理「大量重复元素」）
//
//   把数组分成三段：< pivot  |  == pivot  |  > pivot
//   只需要递归左右两段，中间相等的整段跳过。
//
//   ★ 面试点：普通快排在「全是一样的元素」时是 O(n²)（或 O(n log n) 但退化），
//             三路快排在这种情况下是 O(n)。
// -----------------------------------------------------------------------------
void quick_sort_three_way(std::vector<int>& arr, int lo, int hi) {
    // TODO: 在这里实现
    (void)arr; (void)lo; (void)hi;
}

void quick_sort_three_way(std::vector<int>& arr) {
    if (!arr.empty()) quick_sort_three_way(arr, 0, (int)arr.size() - 1);
}

// =============================================================================
// 测试（已写好，不用改）
// =============================================================================
int main() {
    using namespace tst;
    std::cout << "===== 快速排序 测试 =====\n";

    // --- 基础正确性 ---
    {
        std::vector<int> a{5, 2, 9, 1, 5, 6};
        quick_sort(a);
        check_arr("普通输入 {5,2,9,1,5,6}", a, {1, 2, 5, 5, 6, 9});
    }
    {
        std::vector<int> a;
        quick_sort(a);
        check_arr("空数组", a, {});
    }
    {
        std::vector<int> a{42};
        quick_sort(a);
        check_arr("单元素", a, {42});
    }
    {
        std::vector<int> a{2, 1};
        quick_sort(a);
        check_arr("两个元素（逆序）", a, {1, 2});
    }
    {
        std::vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};
        quick_sort(a);
        check_arr("已经有序（最坏情况候选）", a, {1, 2, 3, 4, 5, 6, 7, 8});
    }
    {
        std::vector<int> a{8, 7, 6, 5, 4, 3, 2, 1};
        quick_sort(a);
        check_arr("完全逆序", a, {1, 2, 3, 4, 5, 6, 7, 8});
    }
    {
        std::vector<int> a{7, 7, 7, 7, 7};
        quick_sort(a);
        check_arr("全部相同", a, {7, 7, 7, 7, 7});
    }
    {
        std::vector<int> a{-3, 0, -1, 2, -3, 5};
        quick_sort(a);
        check_arr("含负数", a, {-3, -3, -1, 0, 2, 5});
    }

    // --- 随机大数组：和 std::sort 对比 ---
    {
        std::mt19937 rng(42);
        std::uniform_int_distribution<int> dist(-10000, 10000);
        std::vector<int> a(20000);
        for (int& x : a) x = dist(rng);

        std::vector<int> expect = a;
        std::sort(expect.begin(), expect.end());

        double ms = time_ms([&] { quick_sort(a); });
        std::cout << "  随机 2 万个数: " << ms << " ms\n";
        check_arr("随机 2 万个数排序正确", a, expect);
    }

    // --- 随机 pivot 版 ---
    {
        std::vector<int> a{5, 2, 9, 1, 5, 6};
        quick_sort_random(a);
        check_arr("随机pivot: {5,2,9,1,5,6}", a, {1, 2, 5, 5, 6, 9});

        std::vector<int> b;
        for (int i = 0; i < 5000; i++) b.push_back(i);   // 已排序 —— 最坏情况输入
        double ms1 = time_ms([&] { quick_sort(b); });
        std::vector<int> c;
        for (int i = 0; i < 5000; i++) c.push_back(i);
        double ms2 = time_ms([&] { quick_sort_random(c); });
        std::cout << "  已排序 5000 个数: 固定pivot = " << ms1
                  << " ms, 随机pivot = " << ms2 << " ms\n";
        std::cout << "  ↑ 这就是「固定选 pivot 会退化」的直接证据\n";
    }

    // --- 三路快排：大量重复元素 ---
    {
        std::vector<int> a(50000, 3);                    // 全一样
        std::vector<int> b = a;
        double ms1 = time_ms([&] { quick_sort(a); });
        double ms2 = time_ms([&] { quick_sort_three_way(b); });
        std::cout << "  5 万个相同元素: 普通快排 = " << ms1
                  << " ms, 三路快排 = " << ms2 << " ms\n";
        std::cout << "  ↑ 这就是三路快排存在的意义\n";
        check_arr("三路快排结果正确", b, std::vector<int>(50000, 3));
    }

    return summary("快速排序");
}
