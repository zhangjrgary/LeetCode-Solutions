Source

leetcode: Find Peak Element | LeetCode OJ * lintcode: (75) Find Peak Element
There is an integer array which has the following features:

    * The numbers in adjacent positions are different.

    * A[0] < A[1] && A[A.length - 2] > A[A.length - 1].

We define a position P is a peek if A[P] > A[P-1] && A[P] > A[P+1].

Find a peak element in this array. Return the index of the peak.

Note
The array may contains multiple peeks, find any of them.

Example
[1, 2, 1, 3, 4, 5, 7, 6]

return index 1 (which is number 2)  or 6 (which is number 7)

Challenge
Time complexity O(logN)
题解1 - lintcode

由时间复杂度的暗示可知应使用二分搜索。首先分析若使用传统的二分搜索，若A[mid] > A[mid - 1] && A[mid] < A[mid + 1]，则找到一个peak为A[mid]；若A[mid - 1] > A[mid]，则A[mid]左侧必定存在一个peak，可用反证法证明：若左侧不存在peak，则A[mid]左侧元素必满足A[0] > A[1] > ... > A[mid -1] > A[mid]，与已知A[0] < A[1]矛盾，证毕。同理可得若A[mid + 1] > A[mid]，则A[mid]右侧必定存在一个peak。如此迭代即可得解。

备注：如果本题是找 first/last peak，就不能用二分法了。

Java

class Solution {
    /**
     * @param A: An integers array.
     * @return: return any of peek positions.
     */
    public int findPeak(int[] A) {
        // write your code here
        if (A == null) {
            return -1;
        }
        if (A.length == 0) {
            return 0;
        }

        int start = 0, end = A.length - 1, mid = end / 2;
        while (start + 1 < end) {
            mid = start + (end - start)/2;
            if (A[mid] < A[mid - 1]) {
                end = mid;
            } else if (A[mid] < A[mid + 1]) {
                start = mid;
            } else {
                return mid;
            }
        }

        mid = (A[start] > A[end]) ? start : end;
        return mid;
    }
}
C++

class Solution {
public:
    /**
     * @param A: An integers array.
     * @return: return any of peek positions.
     */
    int findPeak(vector A) {
        if (A.empty()) {
            return -1;
        }

        vector::size_type start = 0;
        vector::size_type end = A.size() - 1;
        vector::size_type mid = end / 2;

        while (start + 1 < end) {
            mid = start + (end - start) / 2;
            if (A[mid] < A[mid - 1]) {
                end = mid;
            } else if (A[mid] < A[mid + 1]) {
                start = mid;
            } else {
                return mid;
            }
        }

        mid = (A[start] > A[end]) ? start : end;
        return mid;
    }
};
题解2 - leetcode

leetcode 上的题和 lintcode 上有细微的变化，题目如下：

A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1],
find a peak element and return its index.

The array may contain multiple peaks,
in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and
your function should return the index number 2.

click to show spoilers.

Note:
Your solution should be in logarithmic complexity.
如果一开始做的是 leetcode 上的版本而不是 lintcode 上的话，这道题难度要大一些。有了以上的分析基础再来刷 leetcode 上的这道题就是小 case 了，注意题中的关键提示num[-1] = num[n] = -∞, 虽然不像 lintcode 上那么直接，但是稍微变通下也能想到。即num[-1] < num[0] && num[n-1] > num[n], 那么问题来了，这样一来就不能确定峰值 一定存在了，因为给定数组为单调序列的话就咩有峰值了，但是实际情况是——题中有负无穷的假设，也就是说在单调序列的情况下，峰值为数组首部或者尾部元素，谁大就是谁 了。

Java1 - readily understood

public class Solution {
    public int findPeakElement(int[] nums) {
        if (nums == null || nums.length == 0) {
            return -1;
        }

        int start = 0, end = nums.length - 1, mid = end / 2;
        while (start + 1 < end) {
            mid = start + (end - start) / 2;
            if (nums[mid] < nums[mid - 1]) {
                // 1 peak at least in the left side
                end = mid;
            } else if (nums[mid] < nums[mid + 1]) {
                // 1 peak at least in the right side
                start = mid;
            } else {
                return mid;
            }
        }

        mid = (nums[start] > nums[end]) ? start : end;
        return mid;
    }
}
源码分析

典型的二分法模板应用，需要注意的是需要考虑单调序列的特殊情况。当然也可使用紧凑一点的实现如改写循环条件为start < end，这样就不用考虑单调序列了，见实现2.

复杂度分析

二分法，时间复杂度 O(logn).

Java2 - compact implementationleetcode_discussion

public class Solution {
    public int findPeakElement(int[] nums) {
        if (nums == null || nums.length == 0) {
            return -1;
        }

        int start = 0, end = nums.length - 1, mid = end / 2;
        while (start < end) {
            if (nums[mid] < nums[mid + 1]) {
                // 1 peak at least in the right side
                start = mid + 1;
            } else {
                // 1 peak at least in the left side
                end = mid;
            }
            mid = start + (end - start) / 2;
        }

        return start;
    }
}
>

leetcode 和 lintcode 上给的方法名不一样，leetcode 上的为findPeakElement而 lintcode 上为findPeak，弄混的话会编译错误。
