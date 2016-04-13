Source

leetcode: Sqrt(x) | LeetCode OJ * lintcode: (141) Sqrt(x)
题解 - 二分搜索

由于只需要求整数部分，故对于任意正整数 x, 设其整数部分为 k, 显然有 1≤k≤x, 求解 k 的值也就转化为了在有序数组中查找满足某种约束条件的元素，显然二分搜索是解决此类问题的良方。

Python

class Solution:
    # @param {integer} x
    # @return {integer}
    def mySqrt(self, x):
        if x < 0:
            return -1
        elif x == 0:
            return 0

        start, end = 1, x
        while start + 1 < end:
            mid = start + (end - start) / 2
            if mid**2 == x:
                return mid
            elif mid**2 > x:
                end = mid
            else:
                start = mid

        return start
源码分析

异常检测，先处理小于等于0的值。
使用二分搜索的经典模板，注意不能使用start < end, 否则在给定值1时产生死循环。
最后返回平方根的整数部分start.
二分搜索过程很好理解，关键是最后的返回结果还需不需要判断？比如是取 start, end, 还是 mid? 我们首先来分析下二分搜索的循环条件，由while循环条件start + 1 < end可知，start和end只可能有两种关系，一个是end == 1 || end ==2这一特殊情况，返回值均为1，另一个就是循环终止时start恰好在end前一个元素。设值 x 的整数部分为 k, 那么在执行二分搜索的过程中 start≤k≤end 关系一直存在，也就是说在没有找到 mid​2​​==x 时，循环退出时有 startstart了。

复杂度分析

经典的二分搜索，时间复杂度为 O(logn), 使用了start, end, mid变量，空间复杂度为 O(1).
