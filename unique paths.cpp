Unique Paths
Source

lintcode: (114) Unique Paths
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Note
m and n will be at most 100.
题解

题目要求：给定m x n矩阵，求左上角到右下角的路径总数，每次只能向左或者向右前进。按照动态规划中矩阵类问题的通用方法：

State: f[m][n] 从起点到坐标(m,n)的路径数目
Function: f[m][n] = f[m-1][n] + f[m][n-1] 分析终点与左边及右边节点的路径数，发现从左边或者右边到达终点的路径一定不会重合，相加即为唯一的路径总数
Initialization: f[i][j] = 1, 到矩阵中任一节点均至少有一条路径，其实关键之处在于给第0行和第0列初始化，免去了单独遍历第0行和第0列进行初始化
Answer: f[m - 1][n - 1]
C++

class Solution {
public:
    /**
     * @param n, m: positive integer (1 <= n ,m <= 100)
     * @return an integer
     */
    int uniquePaths(int m, int n) {
        if (m < 1 || n < 1) {
            return 0;
        }

        vector > ret(m, vector(n, 1));

        for (int i = 1; i != m; ++i) {
            for (int j = 1; j != n; ++j) {
                ret[i][j] = ret[i - 1][j] + ret[i][j - 1];
            }
        }

        return ret[m - 1][n - 1];
    }
};
源码分析

异常处理，虽然题目有保证为正整数，但还是判断一下以防万一
初始化二维矩阵，值均为1
按照转移矩阵函数进行累加
任何ret[m - 1][n - 1]
Unique Paths II

Source

lintcode: (115) Unique Paths II
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.
Note
m and n will be at most 100.

Example
For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.
题解

在上题的基础上加了obstacal这么一个限制条件，那么也就意味着凡是遇到障碍点，其路径数马上变为0，需要注意的是初始化环节和上题有较大不同。首先来看看错误 的初始化实现。

C++ initialization error

class Solution {
public:
    /**
     * @param obstacleGrid: A list of lists of integers
     * @return: An integer
     */
    int uniquePathsWithObstacles(vector > &obstacleGrid) {
        if(obstacleGrid.empty() || obstacleGrid[0].empty()) {
            return 0;
        }

        const int M = obstacleGrid.size();
        const int N = obstacleGrid[0].size();

        vector > ret(M, vector(N, 0));

        for (int i = 0; i != M; ++i) {
            if (0 == obstacleGrid[i][0]) {
                ret[i][0] = 1;
            }
        }
        for (int i = 0; i != N; ++i) {
            if (0 == obstacleGrid[0][i]) {
                ret[0][i] = 1;
            }
        }

        for (int i = 1; i != M; ++i) {
            for (int j = 1; j != N; ++j) {
                if (obstacleGrid[i][j]) {
                    ret[i][j] = 0;
                } else {
                    ret[i][j] = ret[i -1][j] + ret[i][j - 1];
                }
            }
        }

        return ret[M - 1][N - 1];
    }
};
源码分析

错误之处在于初始化第0行和第0列时，未考虑到若第0行/列有一个坐标出现障碍物，则当前行/列后的元素路径数均为0！

C++

class Solution {
public:
    /**
     * @param obstacleGrid: A list of lists of integers
     * @return: An integer
     */
    int uniquePathsWithObstacles(vector > &obstacleGrid) {
        if(obstacleGrid.empty() || obstacleGrid[0].empty()) {
            return 0;
        }

        const int M = obstacleGrid.size();
        const int N = obstacleGrid[0].size();

        vector > ret(M, vector(N, 0));

        for (int i = 0; i != M; ++i) {
            if (obstacleGrid[i][0]) {
                break;
            } else {
                ret[i][0] = 1;
            }
        }
        for (int i = 0; i != N; ++i) {
            if (obstacleGrid[0][i]) {
                break;
            } else {
                ret[0][i] = 1;
            }
        }

        for (int i = 1; i != M; ++i) {
            for (int j = 1; j != N; ++j) {
                if (obstacleGrid[i][j]) {
                    ret[i][j] = 0;
                } else {
                    ret[i][j] = ret[i -1][j] + ret[i][j - 1];
                }
            }
        }

        return ret[M - 1][N - 1];
    }
};
源码分析

异常处理
初始化二维矩阵(全0阵)，尤其注意遇到障碍物时应break跳出当前循环
递推路径数
返回`ret[M - 1][N - 1]
