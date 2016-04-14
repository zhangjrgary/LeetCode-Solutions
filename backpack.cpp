Source

lintcode: (92) Backpack
Given n items with size A[i], an integer m denotes the size of a backpack. How full you can fill this backpack?

Note
You can not divide any item into small pieces.

Example
If we have 4 items with size [2, 3, 5, 7], the backpack size is 11, we can select 2, 3 and 5, so that the max size we can fill this backpack is 10. If the backpack size is 12. we can select [2, 3, 7] so that we can fulfill the backpack.

You function should return the max size we can fill in the given backpack.
题解

本题是典型的01背包问题，每种类型的物品最多只能选择一件。先来看看 九章算法 的### 题解

状态: result[i][S] 表示前i个物品，取出一些物品能否组成体积和为S的背包
状态转移方程: f[i][S]=f[i−1][S−A[i]] or f[i−1][S] (A[i]为第i个物品的大小)
欲从前i个物品中取出一些组成体积和为S的背包，可从两个状态转换得到。
f[i−1][S−A[i]]: 放入第i个物品，前 i−1 个物品能否取出一些体积和为 S−A[i] 的背包。
f[i−1][S]: 不放入第i个物品，前 i−1 个物品能否取出一些组成体积和为S的背包。
状态初始化: f[1⋯n][0]=true; f[0][1⋯m]=false. 前1~n个物品组成体积和为0的背包始终为真，其他情况为假。
返回结果: 寻找使 f[n][S] 值为true的最大S (1≤S≤m)
C++ 2D vector for result

class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector A) {
        if (A.empty() || m < 1) {
            return 0;
        }

        const int N = A.size() + 1;
        const int M = m + 1;
        vector > result;
        result.resize(N);
        for (vector::size_type i = 0; i != N; ++i) {
            result[i].resize(M);
            std::fill(result[i].begin(), result[i].end(), false);
        }

        result[0][0] = true;
        for (int i = 1; i != N; ++i) {
            for (int j = 0; j != M; ++j) {
                if (j < A[i - 1]) {
                    result[i][j] = result[i - 1][j];
                } else {
                    result[i][j] = result[i - 1][j] || result[i - 1][j - A[i - 1]];
                }
            }
        }

        // return the largest i if true
        for (int i = M; i > 0; --i) {
            if (result[N - 1][i - 1]) {
                return (i - 1);
            }
        }
        return 0;
    }
};
源码分析

异常处理
初始化结果矩阵，注意这里需要使用resize而不是reserve，否则可能会出现段错误
实现状态转移逻辑，一定要分j < A[i - 1]与否来讨论
返回结果，只需要比较result[N - 1][i - 1]的结果，返回true的最大值
状态转移逻辑中代码可以进一步简化，即：

        for (int i = 1; i != N; ++i) {
            for (int j = 0; j != M; ++j) {
                result[i][j] = result[i - 1][j];
                if (j >= A[i - 1] && result[i - 1][j - A[i - 1]]) {
                    result[i][j] = true;
                }
            }
        }
考虑背包问题的核心——状态转移方程，如何优化此转移方程？原始方案中用到了二维矩阵来保存result，注意到result的第i行仅依赖于第i-1行的结果，那么 能否用一维数组来代替这种隐含的关系呢？我们在内循环j处递减即可。如此即可避免result[i][S]的值由本轮result[i][S-A[i] ]递推得到。

C++ 1D vector for result

class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector A) {
        if (A.empty() || m < 1) {
            return 0;
        }

        const int N = A.size();
        vector result;
        result.resize(m + 1);
        std::fill(result.begin(), result.end(), false);

        result[0] = true;
        for (int i = 0; i != N; ++i) {
            for (int j = m; j >= 0; --j) {
                if (j >= A[i] && result[j - A[i]]) {
                    result[j] = true;
                }
            }
        }

        // return the largest i if true
        for (int i = m; i > 0; --i) {
            if (result[i]) {
                return i;
            }
        }
        return 0;
    }
};
Backpack II

Source

lintcode: (125) Backpack II
Given n items with size A[i] and value V[i], and a backpack with size m. What's the maximum value can you put into the backpack?

Note
You cannot divide item into small pieces and the total size of items you choose should smaller or equal to m.
Example
Given 4 items with size [2, 3, 5, 7] and value [1, 5, 2, 4], and a backpack with size 10. The maximum value is 9.
题解

首先定义状态 K(i,w) 为前 i 个物品放入size为 w 的背包中所获得的最大价值，则相应的状态转移方程为： K(i,w)=max{K(i−1,w),K(i−1,w−w​i​​)+v​i​​}

详细分析过程见本节。

C++ 2D vector for result

class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A & V: Given n items with size A[i] and value V[i]
     * @return: The maximum value
     */
    int backPackII(int m, vector A, vector V) {
        if (A.empty() || V.empty() || m < 1) {
            return 0;
        }
        const int N = A.size() + 1;
        const int M = m + 1;
        vector > result;
        result.resize(N);
        for (vector::size_type i = 0; i != N; ++i) {
            result[i].resize(M);
            std::fill(result[i].begin(), result[i].end(), 0);
        }

        for (vector::size_type i = 1; i != N; ++i) {
            for (int j = 0; j != M; ++j) {
                if (j < A[i - 1]) {
                    result[i][j] = result[i - 1][j];
                } else {
                    int temp = result[i - 1][j - A[i - 1]] + V[i - 1];
                    result[i][j] = max(temp, result[i - 1][j]);
                }
            }
        }

        return result[N - 1][M - 1];
    }
};
源码分析

使用二维矩阵保存结果result
返回result矩阵的右下角元素——背包size限制为m时的最大价值
按照第一题backpack的思路，这里可以使用一维数组进行空间复杂度优化。优化方法为逆序求result[j]，优化后的代码如下：

C++ 1D vector for result

class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A & V: Given n items with size A[i] and value V[i]
     * @return: The maximum value
     */
    int backPackII(int m, vector A, vector V) {
        if (A.empty() || V.empty() || m < 1) {
            return 0;
        }

        const int M = m + 1;
        vector result;
        result.resize(M);
        std::fill(result.begin(), result.end(), 0);

        for (vector::size_type i = 0; i != A.size(); ++i) {
            for (int j = m; j >= 0; --j) {
                if (j < A[i]) {
                    // result[j] = result[j];
                } else {
                    int temp = result[j - A[i]] + V[i];
                    result[j] = max(temp, result[j]);
                }
            }
        }

        return result[M - 1];
    }
};
