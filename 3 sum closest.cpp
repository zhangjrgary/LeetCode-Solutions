Source

leetcode: 3Sum Closest | LeetCode OJ * lintcode: (59) 3 Sum Closest
题解1 - 排序 + 2 Sum + 两根指针 + 优化过滤

和 3 Sum 的思路接近，首先对原数组排序，随后将3 Sum 的题拆解为『1 Sum + 2 Sum』的题，对于 Closest 的题使用两根指针而不是哈希表的方法较为方便。对于有序数组来说，在查找 Cloest 的值时其实是有较大的优化空间的。

Python

class Solution:
    """
    @param numbers: Give an array numbers of n integer
    @param target : An integer
    @return : return the sum of the three integers, the sum closest target.
    """
    def threeSumClosest(self, numbers, target):
        result = 2**31 - 1
        length = len(numbers)
        if length < 3:
            return result

        numbers.sort()
        larger_count = 0
        for i, item_i in enumerate(numbers):
            start = i + 1
            end = length - 1
            # optimization 1 - filter the smallest sum greater then target
            if start < end:
                sum3_smallest = numbers[start] + numbers[start + 1] + item_i
                if sum3_smallest > target:
                    larger_count += 1
                    if larger_count > 1:
                        return result

            while (start < end):
                sum3 = numbers[start] + numbers[end] + item_i
                if abs(sum3 - target) < abs(result - target):
                    result = sum3

                # optimization 2 - filter the sum3 closest to target
                sum_flag = 0
                if sum3 > target:
                    end -= 1
                    if sum_flag == -1:
                        break
                    sum_flag = 1
                elif sum3 < target:
                    start += 1
                    if sum_flag == 1:
                        break
                    sum_flag = -1
                else:
                    return result

        return result
源码分析

leetcode 上不让自己导入sys包，保险起见就初始化了result为还算较大的数，作为异常的返回值。
对数组进行排序。
依次遍历排序后的数组，取出一个元素item_i后即转化为『2 Sum Cloest』问题。『2 Sum Cloest』的起始元素索引为i + 1，之前的元素不能参与其中。
优化一——由于已经对原数组排序，故遍历原数组时比较最小的三个元素和target值，若第二次大于target果断就此罢休，后面的值肯定越来越大。
两根指针求『2 Sum Cloest』，比较sum3和result与target的差值的绝对值，更新result为较小的绝对值。
再度对『2 Sum Cloest』进行优化，仍然利用有序数组的特点，若处于『一大一小』的临界值时就可以马上退出了，后面的元素与target之差的绝对值只会越来越大。
复杂度分析

对原数组排序，平均时间复杂度为 O(nlogn), 两重for循环，由于有两处优化，故最坏的时间复杂度才是 O(n​2​​), 使用了result作为临时值保存最接近target的值，两处优化各使用了一个辅助变量，空间复杂度 O(1).
