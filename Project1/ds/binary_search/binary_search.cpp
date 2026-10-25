// =============================================================================
// 二分查找 —— 空文件手写练习
// =============================================================================
//
// 【为什么二分要单独练】
//   二分是「思路 30 秒，写对 30 分钟」的典型：
//   区间的开闭、mid 的取法、循环条件、返回值，四处只要有一处不一致就死循环或越界。
//
//   典型场景：配置表查表 —— 就是「在有序数组里找 key」。
//
// 【面试会问的】
//   1. mid = (lo+hi)/2 有什么问题？怎么写才不溢出？
//      如果hi是INT_MAX那加lo会溢出错误，用lo+(hi-lo)/2是一样的
//   2. 左闭右闭 [lo,hi] 和左闭右开 [lo,hi) 两种写法，循环条件分别是什么？
//      左闭右闭是lo<=hi，左闭右开是lo<hi
//   3. lower_bound / upper_bound 的区别？「第一个 >= x」和「第一个 > x」
//      lower_bound 把等于 target的元素算作候选（留在右边）；
//      upper_bound 把等于 target的元素排除掉（推到左边）。
//      所以前者找第一个 ≥，后者找第一个 > 。
//   4. 二分只能用在有序数组上吗？（不是 —— 只要问题有「单调性」就能二分，LC162 峰值就是例子）
//      不是只能用在有序数组上。 二分的真正前提是：能构造出一个单调的「是/否」判断，
//      使得答案的一侧全是「是」、另一侧全是「否」。
//      有序数组 → arr[i] >= x 天然单调
//      旋转数组 → 哪一半有序 可判定
//      找峰值 → 上坡方向 保证有峰
//      找出单调性并找转折点and局部决策 + 必然存在
// 
// 【编译运行】
//   cmake --build build --config Debug --target ds_binary_search_binary_search
// =============================================================================

#include "test_util.h"
#include <random>

// -----------------------------------------------------------------------------
// TODO 1：基础二分查找 —— 在有序数组里找 target，返回下标；找不到返回 -1
//
//   用「左闭右闭」区间 [lo, hi]：
//     while (lo <= hi) {
//         mid = lo + (hi - lo) / 2;     ← ★ 为什么不用 (lo+hi)/2？
//         ...
//         else lo = mid + 1;  /  hi = mid - 1;
//     }
//
//   ★ 面试点：(lo + hi) / 2 在 lo、hi 都接近 INT_MAX 时会溢出。
//             lo + (hi - lo) / 2 不会。
// -----------------------------------------------------------------------------
int binary_search(const std::vector<int>& arr, int target) {
    // TODO: 在这里实现
    int lo = 0;
    int hi = (int)arr.size()-1;
    while (lo<=hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid]<target) {
            lo = mid+1;
        }
        else if (arr[mid]>target) {
            hi = mid-1;
        }
        else {
            return mid;
        }
    }
    return -1;
    //(void)arr; (void)target;
    //return -2;   // 故意返回一个不可能的值，让测试明显失败
}

// -----------------------------------------------------------------------------
// TODO 2：lower_bound —— 返回「第一个 >= target」的下标
//
//   如果所有元素都 < target，返回 arr.size()
//
//   ⚠️ 这是二分最容易写错的一个。用「左闭右开」区间 [lo, hi) 会更好写：
//      while (lo < hi) {
//          mid = lo + (hi - lo) / 2;
//          if (arr[mid] < target) lo = mid + 1;
//          else                   hi = mid;      ← ★ 注意不是 mid-1
//      }
//      return lo;
//
//   ★ 面试点：为什么这里 hi = mid，而不是 mid - 1？
//           因为 arr[mid] 可能就是答案，不能排除掉。
// -----------------------------------------------------------------------------
int lower_bound(const std::vector<int>& arr, int target) {
    // TODO: 在这里实现
    int lo = 0;
    int hi = (int)arr.size();   //要是target大于数组中所有元素，就返回最后一个元素
    while (lo<hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid]<target) {
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }
    return lo;
    //(void)arr; (void)target;
    //return -2;
}

// -----------------------------------------------------------------------------
// TODO 3：upper_bound —— 返回「第一个 > target」的下标
//
//   只和 lower_bound 差一个比较符号：
//      if (arr[mid] <= target) lo = mid + 1;
//      else                    hi = mid;
//
//   ★ 用法：target 出现的区间是 [lower_bound, upper_bound)
//          出现次数 = upper_bound - lower_bound
// -----------------------------------------------------------------------------
int upper_bound(const std::vector<int>& arr, int target) {
    // TODO: 在这里实现
    int lo = 0;
    int hi = (int)arr.size();
    while (lo<hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) {
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }
    return lo;
    //(void)arr; (void)target;
    //return -2;
}

// -----------------------------------------------------------------------------
// TODO 4：搜索旋转排序数组（LeetCode 33）
//
//   数组是「升序数组」在某点旋转得到的，比如 [4,5,6,7,0,1,2]（原数组 [0..7] 在 4 处旋转）。
//   要求 O(log n) 找到 target。
//
//   思路：每次二分后，左半段和右半段里必然有一段是有序的。
//         先判断哪一段有序，再看 target 是否在有序的那一段里，据此缩小范围。
//
//   ★ 面试点：这题的本质是「二分的适用条件是单调性，不是有序性」——
//            旋转数组整体无序，但「哪一段有序」是可判断的。
// -----------------------------------------------------------------------------
int search_rotated(const std::vector<int>& arr, int target) {
    // TODO: 在这里实现
    int lo = 0;
    int hi = (int)arr.size() - 1;
    while (lo<=hi) {
        int mid = lo + (hi-lo) / 2;
        if (arr[mid]==target) return mid;
        if (arr[lo]<=arr[mid]) {
            if (arr[lo] <= target && arr[mid] > target){
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }
        else {
            if (arr[mid] < target && arr[hi] >= target) {
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
    }
    return -1;
    //(void)arr; (void)target;
    //return -2;
}

// -----------------------------------------------------------------------------
// TODO 5：寻找峰值（LeetCode 162）
//
//   nums[i] != nums[i+1]，返回任意一个峰值下标（比左右都大的元素）。
//   要求 O(log n)。
//
//   思路：比较 nums[mid] 和 nums[mid+1]：
//      nums[mid] < nums[mid+1]  → 右边一定有峰值，lo = mid + 1
//      nums[mid] > nums[mid+1]  → 左边一定有峰值（含 mid），hi = mid
//
//   ★ 面试点：这题说明了「二分不要求数组有序，只要求能判断答案在哪半边」。
// -----------------------------------------------------------------------------
int find_peak(const std::vector<int>& arr) {
    // TODO: 在这里实现
    int lo = 0;
    int hi = (int)arr.size()-1;
    while (lo<hi) {
        int mid = lo + (hi-lo) / 2;
        if (arr[mid] < arr[mid +1 ]) {
            lo = mid+1;
        }
        else {
            hi = mid;
        }
    }
    return lo;
    //(void)arr;
    //return -2;
}

// =============================================================================
// 测试（已写好，不用改）
// =============================================================================
int main() {
    using namespace tst;
    std::cout << "===== 二分查找 测试 =====\n";

    const std::vector<int> v{-9, -3, 0, 1, 3, 3, 3, 7, 11, 20};

    std::cout << "\n[基础二分] 数组 = {-9,-3,0,1,3,3,3,7,11,20}\n";
    check("找 -9（第一个）",     binary_search(v, -9),  0);
    check("找 20（最后一个）",   binary_search(v, 20),  9);
    check("找 3（中间重复）",    binary_search(v, 3) >= 0 ? 1 : 0, 1);
    check("找 1",                binary_search(v, 1),   3);
    check("找 100（不存在）",    binary_search(v, 100), -1);
    check("找 -100（不存在）",   binary_search(v, -100),-1);
    check("找 4（不存在但中间）", binary_search(v, 4),  -1);
    { std::vector<int> e; check("空数组", binary_search(e, 1), -1); }
    { std::vector<int> one{5}; check("单元素-命中", binary_search(one, 5), 0);
                               check("单元素-未命中", binary_search(one, 6), -1); }

    std::cout << "\n[lower_bound] 第一个 >= target 的下标\n";
    check("lower_bound(3)  → 4（第一个 3 的位置）", lower_bound(v, 3), 4);
    check("lower_bound(2)  → 4（没有 2，返回第一个 >2 的）", lower_bound(v, 2), 4);
    check("lower_bound(-9) → 0", lower_bound(v, -9), 0);
    check("lower_bound(-100) → 0", lower_bound(v, -100), 0);
    check("lower_bound(100) → 10（size）", lower_bound(v, 100), 10);

    std::cout << "\n[upper_bound] 第一个 > target 的下标\n";
    check("upper_bound(3)  → 7", upper_bound(v, 3), 7);
    check("upper_bound(7)  → 8", upper_bound(v, 7), 8);
    check("upper_bound(100) → 10（size）", upper_bound(v, 100), 10);
    check("3 出现次数 = upper - lower", upper_bound(v, 3) - lower_bound(v, 3), 3);

    std::cout << "\n[旋转数组] \n";
    { std::vector<int> r{4,5,6,7,0,1,2};
      check("旋转数组找 0 → 4", search_rotated(r, 0), 4);
      check("旋转数组找 4 → 0", search_rotated(r, 4), 0);
      check("旋转数组找 2 → 6", search_rotated(r, 2), 6);
      check("旋转数组找 3 → -1", search_rotated(r, 3), -1);
      std::vector<int> r1{1};
      check("旋转数组单元素命中 → 0", search_rotated(r1, 1), 0);
      check("旋转数组单元素未命中 → -1", search_rotated(r1, 0), -1);
      std::vector<int> r3{5,1,3};
      check("旋转数组 {5,1,3} 找 3 → 2", search_rotated(r3, 3), 2);
    }

    std::cout << "\n[寻找峰值] 返回任意峰值下标\n";
    {
        auto is_peak = [](const std::vector<int>& a, int i) {
            if (i < 0 || i >= (int)a.size()) return false;
            bool l = (i == 0) || a[i] > a[i-1];
            bool r = (i == (int)a.size()-1) || a[i] > a[i+1];
            return l && r;
        };
        std::vector<std::vector<int>> cases = {
            {1,2,3,1}, {1,2,1,3,5,6,4}, {1}, {1,2}, {2,1}, {1,3,2}
        };
        for (auto& c : cases) {
            int p = find_peak(c);
            check_true("峰值: " + [&]{ std::string s; for(int x:c) s+=std::to_string(x)+" "; return s; }(),
                       is_peak(c, p));
        }
    }

    return summary("二分查找");
}
