Source

lintcode: (139) Subarray Sum Closest
Given an integer array, find a subarray with sum closest to zero.
Return the indexes of the first number and last number.

Example
Given [-3, 1, 1, -3, 5], return [0, 2], [1, 3], [1, 1], [2, 2] or [0, 4]

Challenge
O(nlogn) time
题解

题 Zero Sum Subarray | Data Structure and Algorithm 的变形题，由于要求的子串和不一定，故哈希表的方法不再适用，使用解法4 - 排序即可在 O(nlogn) 内解决。具体步骤如下：

首先遍历一次数组求得子串和。
对子串和排序。
逐个比较相邻两项差值的绝对值，返回差值绝对值最小的两项。
C++

class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number
     *          and the index of the last number
     */
    vector subarraySumClosest(vector nums){
        vector result;
        if (nums.empty()) {
            return result;
        }

        const int num_size = nums.size();
        vector > sum_index(num_size + 1);

        for (int i = 0; i < num_size; ++i) {
            sum_index[i + 1].first = sum_index[i].first + nums[i];
            sum_index[i + 1].second = i + 1;
        }

        sort(sum_index.begin(), sum_index.end());

        int min_diff = INT_MAX;
        int closest_index = 1;
        for (int i = 1; i < num_size + 1; ++i) {
            int sum_diff = abs(sum_index[i].first - sum_index[i - 1].first);
            if (min_diff > sum_diff) {
                min_diff = sum_diff;
                closest_index = i;
            }
        }

        int left_index = min(sum_index[closest_index - 1].second,\
                             sum_index[closest_index].second);
        int right_index = -1 + max(sum_index[closest_index - 1].second,\
                                   sum_index[closest_index].second);
        result.push_back(left_index);
        result.push_back(right_index);
        return result;
    }
};
源码分析

为避免对单个子串和是否为最小情形的单独考虑，我们可以采取类似链表 dummy 节点的方法规避，简化代码实现。故初始化sum_index时需要num_size + 1个。这里为避免 vector 反复扩充空间降低运行效率，使用resize一步到位。sum_index即最后结果中left_index和right_index等边界可以结合简单例子分析确定。

复杂度分析

遍历一次求得子串和时间复杂度为 O(n), 空间复杂度为 O(n+1).
对子串和排序，平均时间复杂度为 O(nlogn).
遍历排序后的子串和数组，时间复杂度为 O(n).
总的时间复杂度为 O(nlogn), 空间复杂度为 O(n).
