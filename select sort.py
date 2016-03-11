Selection Sort - 选择排序
核心：不断地选择剩余元素中的最小者。

找到数组中最小元素并将其和数组第一个元素交换位置。
在剩下的元素中找到最小元素并将其与数组第二个元素交换，直至整个数组排序。
以上排序过程使用 Python 实现如下所示：

#!/usr/bin/env python


def selectionSort(alist):
    for i in xrange(len(alist)):
        print(alist)
        min_index = i
        for j in xrange(i + 1, len(alist)):
            if alist[j] < alist[min_index]:
                min_index = j
        alist[min_index], alist[i] = alist[i], alist[min_index]
    return alist

unsorted_list = [8, 5, 2, 6, 9, 3, 1, 4, 0, 7]
print(selectionSort(unsorted_list))
性质：

比较次数=(N-1)+(N-2)+(N-3)+...+2+1~N^2/2
交换次数=N
运行时间与输入无关
数据移动最少
