Source

lintcode: (100) Remove Duplicates from Sorted Array
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array A = [1,1,2],

Your function should return length = 2, and A is now [1,2].

Example
题解

使用双指针(下标)，一个指针(下标)遍历vector数组，另一个指针(下标)只取不重复的数置于原vector中。

class Solution {
public:
    /**
     * @param A: a list of integers
     * @return : return an integer
     */
    int removeDuplicates(vector &nums) {
        if (nums.empty()) {
            return 0;
        }

        int size = 0;
        for (vector::size_type i = 0; i != nums.size(); ++i) {
            if (nums[i] != nums[size]) {
                nums[++size] = nums[i];
            }
        }
        return ++size;
    }
};
源码分析

注意最后需要返回的是++size或者size + 1
