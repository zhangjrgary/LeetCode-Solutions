strstr (a.k.a find sub string), is a useful function in string operation.
You task is to implement this function.

For a given source string and a target string,
you should output the "first" index(from 0) of target string in source string.

If target is not exist in source, just return -1.

Example
If source="source" and target="target", return -1.

If source="abcdabcdefg" and target="bcd", return 1.

Challenge
O(n) time.

Clarification
Do I need to implement KMP Algorithm in an interview?

    - Not necessary. When this problem occurs in an interview,
    the interviewer just want to test your basic implementation ability.
题解

对于字符串查找问题，可使用双重for循环解决，效率更高的则为KMP算法。

Java

/**
 * http://www.jiuzhang.com//solutions/implement-strstr
 */
class Solution {
    /**
     * Returns a index to the first occurrence of target in source,
     * or -1  if target is not part of source.
     * @param source string to be scanned.
     * @param target string containing the sequence of characters to match.
     */
    public int strStr(String source, String target) {
        if (source == null || target == null) {
            return -1;
        }

        int i, j;
        for (i = 0; i < source.length() - target.length() + 1; i++) {
            for (j = 0; j < target.length(); j++) {
                if (source.charAt(i + j) != target.charAt(j)) {
                    break;
                } //if
            } //for j
            if (j == target.length()) {
                return i;
            }
        } //for i

        // did not find the target
        return -1;
    }
}
源码分析

边界检查：source和target有可能是空串。
边界检查之下标溢出：注意变量i的循环判断条件，如果是单纯的i < source.length()则在后面的source.charAt(i + j)时有可能溢出。
代码风格：（1）运算符==两边应加空格；（2）变量名不要起s1``s2这类，要有意义，如target``source；（3）即使if语句中只有一句话也要加大括号，即{return -1;}；（4）Java 代码的大括号一般在同一行右边，C++ 代码的大括号一般另起一行；（5）int i, j;声明前有一行空格，是好的代码风格。
不要在for的条件中声明i,j，容易在循环外再使用时造成编译错误，错误代码示例：
Another Similar Question

/**
 * http://www.jiuzhang.com//solutions/implement-strstr
 */
public class Solution {
    public String strStr(String haystack, String needle) {
        if(haystack == null || needle == null) {
            return null;
        }
        int i, j;
        for(i = 0; i < haystack.length() - needle.length() + 1; i++) {
            for(j = 0; j < needle.length(); j++) {
                if(haystack.charAt(i + j) != needle.charAt(j)) {
                    break;
                }
            }
            if(j == needle.length()) {
                return haystack.substring(i);
            }
        }
        return null;
    }
}
