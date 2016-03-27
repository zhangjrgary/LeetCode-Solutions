Source

GeeksforGeeks: Find subarray with given sum - GeeksforGeeks
Given an nonnegative integer array, find a subarray where the sum of numbers is k.
Your code should return the index of the first number and the index of the last number.

Example
Given [1, 4, 20, 3, 10, 5], sum k = 33, return [2, 4].
题解1 - 哈希表

题 Zero Sum Subarray | Data Structure and Algorithm 的升级版，这道题求子串和为 K 的索引。首先我们可以考虑使用时间复杂度相对较低的哈希表解决。前一道题的核心约束条件为 f(i​1​​)−f(i​2​​)=0，这道题则变为 f(i​1​​)−f(i​2​​)=k

C++

#include 
#include 
#include 

using namespace std;

class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number
     *          and the index of the last number
     */
    vector subarraySum(vector nums, int k){
        vector result;
        // curr_sum for the first item, index for the second item
        // unordered_map hash;
        map hash;
        hash[0] = 0;

        int curr_sum = 0;
        for (int i = 0; i != nums.size(); ++i) {
            curr_sum += nums[i];
            if (hash.find(curr_sum - k) != hash.end()) {
                result.push_back(hash[curr_sum - k]);
                result.push_back(i);
                return result;
            } else {
                hash[curr_sum] = i + 1;
            }
        }

        return result;
    }
};

int main(int argc, char *argv[])
{
    int int_array1[] = {1, 4, 20, 3, 10, 5};
    int int_array2[] = {1, 4, 0, 0, 3, 10, 5};
    vector vec_array1;
    vector vec_array2;
    for (int i = 0; i != sizeof(int_array1) / sizeof(int); ++i) {
        vec_array1.push_back(int_array1[i]);
    }
    for (int i = 0; i != sizeof(int_array2) / sizeof(int); ++i) {
        vec_array2.push_back(int_array2[i]);
    }

    Solution solution;
    vector result1 = solution.subarraySum(vec_array1, 33);
    vector result2 = solution.subarraySum(vec_array2, 7);

    cout << "result1 = [" << result1[0] << " ," << result1[1] << "]" << endl;
    cout << "result2 = [" << result2[0] << " ," << result2[1] << "]" << endl;

    return 0;
}
源码分析

与 Zero Sum Subarray 题的变化之处有两个地方，第一个是判断是否存在哈希表中时需要使用hash.find(curr_sum - k), 最终返回结果使用result.push_back(hash[curr_sum - k]);而不是result.push_back(hash[curr_sum]);

复杂度分析

略，见 Zero Sum Subarray | Data Structure and Algorithm

题解2 - 利用单调函数特性

不知道细心的你是否发现这道题的隐含条件——nonnegative integer array, 这也就意味着子串和函数 f(i) 为「单调不减」函数。单调函数在数学中可是重点研究的对象，那么如何将这种单调性引入本题中呢？不妨设 i​2​​>i​1​​, 题中的解等价于寻找 f(i​2​​)−f(i​1​​)=k, 则必有 f(i​2​​)≥k.

我们首先来举个实际例子帮助分析，以整数数组 {1, 4, 20, 3, 10, 5} 为例，要求子串和为33的索引值。首先我们可以构建如下表所示的子串和 f(i).

f(i)	1	5	25	28	38
i	0	1	2	3	4
要使部分子串和为33，则要求的第二个索引值必大于等于4，如果索引值再继续往后遍历，则所得的子串和必大于等于38，进而可以推断出索引0一定不是解。那现在怎么办 咧？当然是把它扔掉啊！第一个索引值往后递推，直至小于33时又往后递推第二个索引值，于是乎这种技巧又可以认为是「两根指针」。

C++

#include 
#include 
#include 

using namespace std;

class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number
     *          and the index of the last number
     */
    vector subarraySum2(vector nums, int k){
        vector result;

        int left_index = 0;
        int curr_sum = 0;
        for (int i = 0; i != nums.size(); ++i) {
            curr_sum += nums[i];
            if (curr_sum == k) {
                result.push_back(left_index);
                result.push_back(i);
                return result;
            }

            while (curr_sum > k) {
                curr_sum -= nums[left_index];
                ++left_index;
            }
        }

        return result;
    }
};

int main(int argc, char *argv[])
{
    int int_array1[] = {1, 4, 20, 3, 10, 5};
    int int_array2[] = {1, 4, 0, 0, 3, 10, 5};
    vector vec_array1;
    vector vec_array2;
    for (int i = 0; i != sizeof(int_array1) / sizeof(int); ++i) {
        vec_array1.push_back(int_array1[i]);
    }
    for (int i = 0; i != sizeof(int_array2) / sizeof(int); ++i) {
        vec_array2.push_back(int_array2[i]);
    }

    Solution solution;
    vector result1 = solution.subarraySum2(vec_array1, 33);
    vector result2 = solution.subarraySum2(vec_array2, 7);

    cout << "result1 = [" << result1[0] << " ," << result1[1] << "]" << endl;
    cout << "result2 = [" << result2[0] << " ," << result2[1] << "]" << endl;

    return 0;
}
源码分析

使用for循环累加curr_sum, 在curr_sum > k时再使用while递减curr_sum, 同时递增左边索引left_index.

复杂度分析

看似有两重循环，由于仅遍历一次数组，且索引最多挪动和数组等长的次数。故最终时间复杂度近似为 O(2n), 空间复杂度为 O(1).
