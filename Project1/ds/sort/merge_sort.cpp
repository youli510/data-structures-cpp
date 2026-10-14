// =============================================================================
// 归并排序 —— 空文件手写练习
// =============================================================================
//
// 【要求】不看资料，把下面 3 个 TODO 写出来。
//
// 【面试会问的】
//   1. 归并排序的时间/空间复杂度？为什么空间是 O(n)？
//   2. 归并稳定吗？为什么？（对比快排）
//   3. 什么场景下必须用归并而不是快排？
//      提示：LeetCode 148 排序链表 —— 链表上快排为什么不好用？
//   4. 「外部排序」（数据大到内存放不下）为什么必须用归并？
//
// 【编译运行】
//   cmake --build build --config Debug --target ds_sort_merge_sort
// =============================================================================

#include "test_util.h"
#include <random>

// -----------------------------------------------------------------------------
// TODO 1：把两个已经有序的区间 [lo..mid] 和 [mid+1..hi] 合并成一个有序区间
//
//   需要一个临时数组 buf（大小和 arr 一样，可以只开一次重复用）。
//   双指针：i 指向左半段开头，j 指向右半段开头，每次取较小的放进 buf。
//
//   ★ 这就是「合并两个有序数组」——你链表那题（LC21）写过同样的东西。
// -----------------------------------------------------------------------------
void merge(std::vector<int>& arr, std::vector<int>& buf, int lo, int mid, int hi) {
    // TODO: 在这里实现
    (void)arr; (void)buf; (void)lo; (void)mid; (void)hi;
}

// -----------------------------------------------------------------------------
// TODO 2：递归归并排序
//
//   分治三步：分（算 mid）→ 治（递归左右）→ 合（merge）
// -----------------------------------------------------------------------------
void merge_sort(std::vector<int>& arr, std::vector<int>& buf, int lo, int hi) {
    // TODO: 在这里实现
    (void)arr; (void)buf; (void)lo; (void)hi;
}

// 对外接口（已写好）
void merge_sort(std::vector<int>& arr) {
    if (arr.size() < 2) return;
    std::vector<int> buf(arr.size());
    merge_sort(arr, buf, 0, (int)arr.size() - 1);
}

// -----------------------------------------------------------------------------
// TODO 3：链表归并排序（对应 LeetCode 148. 排序链表）
//
//   为什么链表上归并比快排好？
//     快排依赖「随机访问」（arr[mid]、arr[hi]），而链表访问第 k 个元素是 O(k)。
//     归并只需要顺序扫描 + 改指针，正好符合链表的优势。
//
//   三步：
//     ① 快慢指针找中点（你 list_apps.cpp 里写过！）
//     ② 递归排序左右两半
//     ③ 合并两个有序链表（LC21 写过！）
// -----------------------------------------------------------------------------
struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int v) : val(v), next(nullptr) {}
};

ListNode* merge_two(ListNode* a, ListNode* b) {
    // TODO: 合并两个有序链表（可以先写个哑结点 dummy，最后返回 dummy.next）
    (void)a; (void)b;
    return nullptr;
}

ListNode* sort_list(ListNode* head) {
    // TODO: 链表归并排序
    //   递归出口：head == nullptr || head->next == nullptr
    //   找中点：快慢指针，注意要「断开」成两段
    (void)head;
    return nullptr;
}

// =============================================================================
// 测试（已写好，不用改）
// =============================================================================
int main() {
    using namespace tst;
    std::cout << "===== 归并排序 测试 =====\n";

    // --- 基础正确性 ---
    {
        std::vector<int> a{5, 2, 9, 1, 5, 6};
        merge_sort(a);
        check_arr("普通输入 {5,2,9,1,5,6}", a, {1, 2, 5, 5, 6, 9});
    }
    {
        std::vector<int> a;
        merge_sort(a);
        check_arr("空数组", a, {});
    }
    {
        std::vector<int> a{42};
        merge_sort(a);
        check_arr("单元素", a, {42});
    }
    {
        std::vector<int> a{2, 1};
        merge_sort(a);
        check_arr("两个元素（逆序）", a, {1, 2});
    }
    {
        std::vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};
        merge_sort(a);
        check_arr("已经有序", a, {1, 2, 3, 4, 5, 6, 7, 8});
    }
    {
        std::vector<int> a{8, 7, 6, 5, 4, 3, 2, 1};
        merge_sort(a);
        check_arr("完全逆序", a, {1, 2, 3, 4, 5, 6, 7, 8});
    }
    {
        std::vector<int> a{7, 7, 7, 7, 7};
        merge_sort(a);
        check_arr("全部相同", a, {7, 7, 7, 7, 7});
    }
    {
        std::vector<int> a{-3, 0, -1, 2, -3, 5};
        merge_sort(a);
        check_arr("含负数", a, {-3, -3, -1, 0, 2, 5});
    }

    // --- 稳定性验证（归并应该是稳定的）---
    {
        // 用 pair 不好比，改用「带下标的元素」的思路：
        // 这里简单验证「相等元素相对顺序」不是靠值能看出来的，
        // 所以用一个小技巧：把原始下标编码进低位。
        // 更严谨的稳定性测试需要自定义结构体，这里用注释说明即可。
        std::cout << "  注：归并是稳定排序（相等元素保持原顺序）；快排不稳定。\n";
        std::cout << "      想亲手验证的话，可以把元素换成 std::pair<值, 原始下标> 再比下标。\n";
    }

    // --- 随机大数组 ---
    {
        std::mt19937 rng(7);
        std::uniform_int_distribution<int> dist(-100000, 100000);
        std::vector<int> a(50000);
        for (int& x : a) x = dist(rng);
        std::vector<int> expect = a;
        std::sort(expect.begin(), expect.end());

        double ms = time_ms([&] { merge_sort(a); });
        std::cout << "  随机 5 万个数: " << ms << " ms\n";
        check_arr("随机 5 万个数排序正确", a, expect);
    }

    // --- 链表归并（LC148）---
    {
        // 构造 4 -> 2 -> 1 -> 3
        ListNode* head = new ListNode(4);
        head->next = new ListNode(2);
        head->next->next = new ListNode(1);
        head->next->next->next = new ListNode(3);

        ListNode* sorted = sort_list(head);
        std::vector<int> got;
        for (ListNode* p = sorted; p; p = p->next) got.push_back(p->val);
        check_arr("链表 4->2->1->3 排序", got, {1, 2, 3, 4});

        // 清内存（记得自己写的 delete，这是你 graph.cpp 踩过的坑）
        while (sorted) { ListNode* n = sorted->next; delete sorted; sorted = n; }
    }
    {
        ListNode* head = new ListNode(-1);
        head->next = new ListNode(5);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(0);

        ListNode* sorted = sort_list(head);
        std::vector<int> got;
        for (ListNode* p = sorted; p; p = p->next) got.push_back(p->val);
        check_arr("链表 -1->5->3->4->0 排序", got, {-1, 0, 3, 4, 5});

        while (sorted) { ListNode* n = sorted->next; delete sorted; sorted = n; }
    }

    return summary("归并排序");
}
