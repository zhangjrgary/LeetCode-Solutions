Source

leetcode: First Missing Positive | LeetCode OJ * lintcode: (189) First Missing Positive
Given an unsorted integer array, find the first missing positive integer.

Example
Given [1,2,0] return 3, and [3,4,-1,1] return 2.

Challenge
Your algorithm should run in O(n) time and uses constant space.
题解

容易想到的方案是先排序，然后遍历求得缺的最小整数。排序算法中常用的基于比较的方法时间复杂度的理论下界为 O(nlogn), 不符题目要求。常见的能达到线性时间复杂度的排序算法有 基数排序，计数排序 和 桶排序。

基数排序显然不太适合这道题，计数排序对元素落在一定区间且重复值较多的情况十分有效，且需要额外的 O(n) 空间，对这道题不太合适。最后就只剩下桶排序了，桶排序通常需要按照一定规则将值放入桶中，一般需要额外的 O(n) 空间，咋看一下似乎不太适合在这道题中使用，但是若能设定一定的规则原地交换原数组的值呢？这道题的难点就在于这种规则的设定。

设想我们对给定数组使用桶排序的思想排序，第一个桶放1，第二个桶放2，如果找不到相应的数，则相应的桶的值不变(可能为负值，也可能为其他值)。

那么怎么才能做到原地排序呢？即若 A[i]=x, 则将 x 放到它该去的地方 - A[x−1]=x, 同时将原来 A[x−1] 地方的值交换给 A[i].

排好序后遍历桶，如果不满足 f[i]=i+1, 那么警察叔叔就是它了！如果都满足条件怎么办？那就返回给定数组大小再加1呗。

C++

class Solution {
public:
    /**
     * @param A: a vector of integers
     * @return: an integer
     */
    int firstMissingPositive(vector A) {
        const int size = A.size();

        for (int i = 0; i < size; ++i) {
            while (A[i] > 0 && A[i] <= size && \
                  (A[i] != i + 1) && (A[i] != A[A[i] - 1])) {
                int temp = A[A[i] - 1];
                A[A[i] - 1] = A[i];
                A[i] = temp;
            }
        }

        for (int i = 0; i < size; ++i) {
            if (A[i] != i + 1) {
                return i + 1;
            }
        }

        return size + 1;
    }
};
源码分析

核心代码为那几行交换，但是要很好地处理各种边界条件则要下一番功夫了，要能正常的交换，需满足以下几个条件：

A[i] 为正数，负数和零都无法在桶中找到生存空间...
A[i] \leq size 当前索引处的值不能比原数组容量大，大了的话也没用啊，肯定不是缺的第一个正数。
A[i] != i + 1, 都满足条件了还交换个毛线，交换也是自身的值。
A[i] != A[A[i] - 1], 避免欲交换的值和自身相同，否则有重复值时会产生死循环。
如果满足以上四个条件就可以愉快地交换彼此了，使用while循环处理，此时i并不自增，直到将所有满足条件的索引处理完。

注意交换的写法，若写成

int temp = A[i];
A[i] = A[A[i] - 1];
A[A[i] - 1] = temp;
这又是满满的 bug :( 因为在第三行中A[i]已不再是之前的值，第二行赋值时已经改变，故源码中的写法比较安全。

最后遍历桶排序后的数组，若在数组大小范围内找到不满足条件的解，直接返回，否则就意味着原数组给的元素都是从1开始的连续正整数，返回数组大小加1即可。

复杂度分析

「桶排序」需要遍历一次原数组，考虑到while循环也需要一定次数的遍历，故时间复杂度至少为 O(n). 最后求索引值最多遍历一次排序后数组，时间复杂度最高为 O(n), 用到了temp作为中间交换变量，空间复杂度为 O(1).
