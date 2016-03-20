Source

CC150: (158) Two Strings Are Anagrams
Write a method anagram(s,t) to decide if two strings are anagrams or not.

Example
Given s="abcd", t="dcab", return true.

Challenge
O(n) time, O(1) extra space
题解1 - hashmap 统计字频

判断两个字符串是否互为变位词，若区分大小写，考虑空白字符时，直接来理解可以认为两个字符串的拥有各不同字符的数量相同。对于比较字符数量的问题常用的方法为遍历两 个字符串，统计其中各字符出现的频次，若不等则返回false. 有很多简单字符串类面试题都是此题的变形题。

C++

class Solution {
public:
    /**
     * @param s: The first string
     * @param b: The second string
     * @return true or false
     */
    bool anagram(string s, string t) {
        if (s.empty() || t.empty()) {
            return false;
        }
        if (s.size() != t.size()) {
            return false;
        }

        int letterCount[256] = {0};

        for (int i = 0; i != s.size(); ++i) {
            ++letterCount[s[i]];
            --letterCount[t[i]];
        }
        for (int i = 0; i != t.size(); ++i) {
            if (letterCount[t[i]] < 0) {
                return false;
            }
        }

        return true;
    }
};
源码分析

两个字符串长度不等时必不可能为变位词(需要注意题目条件灵活处理)。
初始化含有256个字符的计数器数组。
对字符串 s 自增，字符串 t 递减，再次遍历判断letterCount数组的值，小于0时返回false.
在字符串长度较长(大于所有可能的字符数)时，还可对第二个for循环做进一步优化，即t.size() > 256时，使用256替代t.size(), 使用i替代t[i].

复杂度分析

两次遍历字符串，时间复杂度最坏情况下为 O(2n), 使用了额外的数组，空间复杂度 O(256).

题解2 - 排序字符串

另一直接的解法是对字符串先排序，若排序后的字符串内容相同，则其互为变位词。题解1中使用 hashmap 的方法对于比较两个字符串是否互为变位词十分有效，但是在比较多个字符串时，使用 hashmap 的方法复杂度则较高。

C++

class Solution {
public:
    /**
     * @param s: The first string
     * @param b: The second string
     * @return true or false
     */
    bool anagram(string s, string t) {
        if (s.empty() || t.empty()) {
            return false;
        }
        if (s.size() != t.size()) {
            return false;
        }

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        if (s == t) {
            return true;
        } else {
            return false;
        }
    }
};
源码分析

对字符串 s 和 t 分别排序，而后比较是否含相同内容。对字符串排序时可以采用先统计字频再组装成排序后的字符串，效率更高一点。

复杂度分析

C++的 STL 中 sort 的时间复杂度介于 O(n) 和 O(n​2​​)之间，判断s == t时间复杂度最坏为 O(n).
